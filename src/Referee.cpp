//
// Created by beurie_v on 17/05/17.
//

#include <algorithm>
#include <random>
#include "Referee.hh"
#include "Error.hh"

Referee::Referee(Map &map, uint32_t const playerNbr)
        : _map(map),
          _playerNbr(playerNbr),
          _bombsId(0),
          _powerUpsId(0),
          _boxes(map.getBoxes()),
          _dropRate(25),
          _distrib100(1, 100),
          _distrib4(0, 3) {
    auto const      &spawns = this->_map.getSpawns();

    if (spawns.size() < playerNbr) {
        throw RuntimeError("Referee::ctor", "Not enough spawns on map");
    }
    for (uint32_t i = 0; i < playerNbr; ++i) {
        this->_characters.push_back(Character(i, irr::core::vector3df(spawns[i].getPosition().X,
                                                                      spawns[i].getPosition().Y,
                                                                      spawns[i].getPosition().Z)));
    }
}

Referee::Referee(Referee const &other)
        : _map(other._map),
          _playerNbr(other._playerNbr),
          _bombs(other._bombs),
          _characters(other._characters),
          _bonuses(other._bonuses),
          _boxes(other._boxes) {

}

Referee::~Referee() {

}

void
Referee::doAction(uint32_t const id, Action::Type const &action, float const speed) {
    auto    owner = this->_getOwner(id);

    if (owner != this->_characters.end()) {
        if (action == Action::BOMB) {
            this->_placeBomb(*owner);
        } else {
            this->_move(*owner, action, speed);
        }
    }
}

void
Referee::_placeBomb(Character &owner) {
    this->_bombs.push_back(Bomb(owner.getPosition(), this->_bombsId, owner.getFuse(),
                                owner.getPower(), owner.getId()));
    this->_bombsId++;
    owner.decCap(1);
}

void
Referee::_move(Character &owner, Action::Type const &direction, float const speedCoef) {
    auto speed = speedCoef > 0 ? speedCoef : 2.f;
    auto const &x = owner.getPosition().X;
    auto const &y = owner.getPosition().Y;
    auto const &z = owner.getPosition().Z;
    irr::core::vector3df    pos;
    speed *= owner.getSpeed();

    switch (direction) {
        case Action::UP:
            pos = irr::core::vector3df(x, y, z + speed);
            break;

        case Action::RIGHT:
            pos = irr::core::vector3df(x + speed, y, z);
            break;

        case Action::DOWN:
            pos = irr::core::vector3df(x, y, z - speed);
            break;

        case Action::LEFT:
            pos = irr::core::vector3df(x - speed, y, z);
            break;

        default:
            throw BadArgument("Referee::_move", "Bad action");
    }
    if (this->_isCellAvailable(pos)) {
        owner.setPosition(pos);
        this->_activatePowerUps(owner, pos);
    }
}

std::vector<Character>::iterator
Referee::_getOwner(uint32_t const id) {
    auto    owner = std::find_if(this->_characters.begin(), this->_characters.end(),
                                 [&id](Character const &character) { return character.getId() == id; });
    return owner;
}

void
Referee::_detonate(Bomb const &bomb) {
    std::remove_if(this->_bombs.begin(), this->_bombs.end(),
                   [&bomb](Bomb const &current) { return current.getId() == bomb.getId(); });

    std::array<Action::Type, 4>             dirs = { Action::UP, Action::RIGHT, Action::DOWN, Action::LEFT };
    std::array<AEntity::PowerUpType, 4>     powerUpsTypes { AEntity::SPEED, AEntity::STRENGTH,
                                                            AEntity::SHORTFUSE, AEntity::CAPACITY };
    irr::core::vector3d<int> const         &pos = irr::core::vector3d<int>(static_cast<int>(bomb.getPosition().X),
                                                                           static_cast<int>(bomb.getPosition().Y),
                                                                           static_cast<int>(bomb.getPosition().Z));

    for (size_t j = 0; j < dirs.size(); ++j) {
        for (size_t i = 1; i < bomb.getPower(); ++i) {
            auto    f = [&pos,   &i, &j, &dirs, this](auto const &elem) {
                return irr::core::vector3d<int>(static_cast<int>(elem.getPosition().X),
                                                static_cast<int>(elem.getPosition().Y),
                                                static_cast<int>(elem.getPosition().Z)) ==
                       irr::core::vector3d<int>(this->_getBlast(pos, i, dirs[j]));
            };

            auto const  &playerFound = std::find_if(this->_characters.begin(), this->_characters.end(), f);
            if (playerFound != this->_characters.end()) {
                std::remove_if(this->_characters.begin(), this->_characters.end(),
                               [&playerFound](Character const &currChar) { return currChar.getId() == playerFound->getId(); });
            }

            auto const  &wallFound = std::find_if(this->_map.getWalls().begin(), this->_map.getWalls().end(), f);
            if (wallFound != this->_map.getWalls().end()) {
                break;
            }

            auto const  &bombFound = std::find_if(this->_bombs.begin(), this->_bombs.end(), f);
            if (bombFound != this->_bombs.end()) {
                this->_detonate(*bombFound);
                break;
            }

            auto const  &boxFound = std::find_if(this->_boxes.begin(), this->_boxes.end(), f);
            if (boxFound != this->_boxes.end()) {
                std::remove_if(this->_boxes.begin(), this->_boxes.end(),
                               [&boxFound](Cell const &currBox) { return currBox.getPosition() == boxFound->getPosition(); });
                int const       &rand = this->_distrib100(this->_generator);
                if (rand <= this->_dropRate) {
                    this->_bonuses.push_back(PowerUp(boxFound->getPosition(), this->_powerUpsId,
                                                     powerUpsTypes[this->_distrib4(this->_generator)], 100));
                    this->_powerUpsId++;
                }
                break;
            }

            auto const  &bonusFound = std::find_if(this->_bonuses.begin(), this->_bonuses.end(), f);
            if (bonusFound != this->_bonuses.end()) {
                std::remove_if(this->_bonuses.begin(), this->_bonuses.end(),
                               [&bonusFound](PowerUp const &currPwUp) { return currPwUp.getId() == bonusFound->getId(); });
            }
        }
    }

    auto    owner = this->_getOwner(bomb.getOwner());
    if (owner != this->_characters.end()) {
        owner->incCap(1);
    }
}

Referee const &
Referee::update() {
    for (size_t i = 0; i < this->_bombs.size(); ++i) {
        this->_bombs[i].decTimer();
        if (this->_bombs[i].getTimer() == 0) {
            this->_detonate(this->_bombs[i]);
            i--;
        }
    }
    for (size_t i = 0; i < this->_bonuses.size(); ++i) {
        this->_bonuses[i].decTimer();
        if (this->_bonuses[i].getTimer() == 0) {
            this->_bonuses.erase(this->_bonuses.begin() + i);
            i--;
        }
    }
    return *this;
}

bool
Referee::_isCellAvailable(irr::core::vector3df const &fPos) const {
    irr::core::vector3d<int> const      &iPos = irr::core::vector3d<int>(static_cast<int>(fPos.X),
                                                                         static_cast<int>(fPos.Y),
                                                                         static_cast<int>(fPos.Z));
    auto    f = [&iPos, this](auto const &elem) {
        return irr::core::vector3d<int>(static_cast<int>(elem.getPosition().X),
                                        static_cast<int>(elem.getPosition().Y),
                                        static_cast<int>(elem.getPosition().Z)) == iPos;
    };


    auto const  &wallFound = std::find_if(this->_map.getWalls().begin(), this->_map.getWalls().end(), f);
    if (wallFound != this->_map.getWalls().end()) {
        return false;
    }
    auto const  &bombFound = std::find_if(this->_bombs.begin(), this->_bombs.end(), f);
    if (bombFound != this->_bombs.end()) {
        return false;
    }

    auto const  &boxFound = std::find_if(this->_boxes.begin(), this->_boxes.end(), f);
    if (boxFound != this->_boxes.end()) {
        return false;
    }
    return true;
}

irr::core::vector3d<int> const
Referee::_getBlast(irr::core::vector3d<int> const &pos, size_t const offset, Action::Type const &dir) const {
    switch (dir) {
        case Action::UP:
            return irr::core::vector3d<int>(pos.X, pos.Y - static_cast<int>(offset), pos.Z);

        case Action::RIGHT:
            return irr::core::vector3d<int>(pos.X + static_cast<int>(offset), pos.Y, pos.Z);

        case Action::DOWN:
            return irr::core::vector3d<int>(pos.X, pos.Y + static_cast<int>(offset), pos.Z);

        case Action::LEFT:
            return irr::core::vector3d<int>(pos.X - static_cast<int>(offset), pos.Y, pos.Z);

        default:
            break;
    }
    return pos;
}

void
Referee::_activatePowerUps(Character &player, irr::core::vector3df const &fPos) {
    irr::core::vector3d<int> const      &iPos = irr::core::vector3d<int>(static_cast<int>(fPos.X),
                                                                         static_cast<int>(fPos.Y),
                                                                         static_cast<int>(fPos.Z));

    auto const  &bonusFound = std::find_if(this->_bonuses.begin(), this->_bonuses.end(),
                                           [&iPos, this](auto const &elem) {
                                               return irr::core::vector3d<int>(static_cast<int>(elem.getPosition().X),
                                                                               static_cast<int>(elem.getPosition().Y),
                                                                               static_cast<int>(elem.getPosition().Z)) == iPos;
                                           });
    if (bonusFound != this->_bonuses.end()) {
        switch (bonusFound->getType()) {
            case AEntity::SPEED:
                player.incSpeed(1);
                break;

            case AEntity::STRENGTH:
                player.incPower(1);
                break;

            case AEntity::SHORTFUSE:
                player.decFuse(player.getFuse() / 4);
                break;

            case AEntity::CAPACITY:
                player.incCap(1);
                break;

            default:
                break;
        }
        this->_bonuses.erase(bonusFound);
    }
}
