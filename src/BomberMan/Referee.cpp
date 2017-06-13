//
// Created by beurie_v on 17/05/17.
//

#include <array>
#include "Referee.hh"

Referee::Referee(Map &map, uint32_t const playerNbr)
        : _map(map),
          _playerNbr(playerNbr),
          _bombsId(0),
          _powerUpsId(0),
          _boxes(map.getBoxes()),
          _dropRate(100),
          _distrib100(1, 100),
          _distrib4(0, 3) {
    auto const      &spawns = this->_map.getSpawns();

    if (spawns.size() < playerNbr) {
        throw RuntimeError("Referee::ctor", "Not enough spawns on map");
    }
    for (uint32_t i = 0; i < playerNbr; ++i) {
        this->_characters.push_back(Character(i, irr::core::vector3df(spawns[i].getPosition().X + 0.5f,
                                                                      spawns[i].getPosition().Y,
                                                                      spawns[i].getPosition().Z + 0.5f)));
    }
}

Referee::Referee(Referee const &other)
        : _map(other._map),
          _playerNbr(other._playerNbr),
          _boxes(other._boxes),
          _bombs(other._bombs),
          _bonuses(other._bonuses),
          _characters(other._characters) {
}

Referee::~Referee() {

}

Referee &Referee::operator=(Referee const &other) {
    if (&other != this) {
        this->_map = other._map;
        this->_playerNbr = other._playerNbr;
        this->_bombs = other._bombs;
        this->_characters = other._characters;
        this->_bonuses = other._bonuses;
        this->_boxes = other._boxes;
    }
    return *this;
}

void
Referee::doAction(uint32_t const id, Action::Type const &action, float const speed) {
    auto    owner = this->_getOwner(id);

    if (owner != this->_characters.end()) {
        if (action == Action::BOMB) {
            if (owner->getCapacity() > 0) {
                this->_placeBomb(*owner);
            }
        } else {
            this->_move(*owner, action, speed);
        }
    }
}

void
Referee::_placeBomb(Character &owner) {
    for (size_t i = 0; i < this->_bombs.size(); ++i) {
        if (this->_convertToInt(this->_bombs[i].getPosition()) == this->_convertToInt(owner.getPosition())) {
            return;
        }
    }
    this->_bombs.push_back(Bomb(this->_convertToInt(owner.getPosition()), this->_bombsId, owner.getFuse(),
                                owner.getPower(), owner.getId()));
    this->_bombsId++;
    std::cout << "DECAP Owner : " << owner.getId() << std::endl;
    owner.decCap(1);
}

void
Referee::_move(Character &owner, Action::Type const &direction, float const speedCoef) {
    auto speed = speedCoef > 0 ? speedCoef : SPEED_UNIT;
    auto const &x = owner.getPosition().X;
    auto const &y = owner.getPosition().Y;
    auto const &z = owner.getPosition().Z;
    irr::core::vector3df    pos;
    if (speed != 1) {
        speed *= owner.getSpeed();
    }

    switch (direction) {
        case Action::UP:
            pos = irr::core::vector3df(x, y, z - speed);
            break;

        case Action::RIGHT:
            pos = irr::core::vector3df(x - speed, y, z);
            break;

        case Action::DOWN:
            pos = irr::core::vector3df(x, y, z + speed);
            break;

        case Action::LEFT:
            pos = irr::core::vector3df(x + speed, y, z);
            break;

        default:
            throw BadArgument("Referee::_move" + std::to_string(direction), "Bad action");
    }
    if (this->isCellAvailable(pos) ||
        this->_convertToInt(pos) == this->_convertToInt(owner.getPosition())) {
        owner.setPosition(pos);
        this->_activatePowerUps(owner);
    }
}

std::vector<Character>::iterator
Referee::_getOwner(uint32_t const id) {
    auto    owner = std::find_if(this->_characters.begin(), this->_characters.end(),
                                 [&id](Character const &character) { return character.getId() == id; });
    return owner;
}

void
Referee::_detonate(Bomb &bomb, bool const spawnPowerUps) {
    bomb.setState(true);
    std::array<Action::Type, 4>             dirs = { Action::UP, Action::RIGHT, Action::DOWN, Action::LEFT };
    std::array<AEntity::PowerUpType, 4>     powerUpsTypes = {   AEntity::SPEED, AEntity::STRENGTH,
                                                                AEntity::SHORTFUSE, AEntity::CAPACITY };
    irr::core::vector3d<int> const         pos = this->_convertToInt(bomb.getPosition());

    for (size_t j = 0; j < dirs.size(); ++j) {
        for (size_t i = 0; i < bomb.getPower(); ++i) {
            irr::core::vector3d<int>    blast = this->_getBlast(pos, i, dirs[j]);

            auto    f = [&blast, this](auto const &elem) -> bool {
                return this->_convertToInt(elem.getPosition()) == blast;
            };
            auto const  &playerFound = std::find_if(this->_characters.begin(), this->_characters.end(), f);
            if (playerFound != this->_characters.end()) {
                this->_characters.erase(playerFound);
            }

            auto const  &wallFound = std::find_if(this->_map.getWalls().begin(), this->_map.getWalls().end(), f);
            if (wallFound != this->_map.getWalls().end()) {
                break;
            }

            auto const  &bombFound = std::find_if(this->_bombs.begin(), this->_bombs.end(),
                                                  [&blast, &bomb, this](Bomb const &elem) {
                                                      return (bomb.getId() != elem.getId()) &&
                                                             (elem.getState() == false) &&
                                                             (blast == this->_convertToInt(elem.getPosition()));
                                                  });
            if (bombFound != this->_bombs.end()) {
                this->_detonate(*bombFound, spawnPowerUps);
                break;
            }
            auto const  &boxFound = std::find_if(this->_boxes.begin(), this->_boxes.end(), f);
            if (boxFound != this->_boxes.end()) {
                auto rand = static_cast<uint32_t>(this->_distrib100(this->_generator));
                if (spawnPowerUps && rand <= this->_dropRate) {
                    this->_bonuses.push_back(PowerUp(this->_convertToInt(boxFound->getPosition()), this->_powerUpsId,
                                                     powerUpsTypes[this->_distrib4(this->_generator)], 500));
                    /*this->_bonuses.push_back(PowerUp(this->_convertToInt(boxFound->getPosition()), this->_powerUpsId,
                                                     powerUpsTypes[0], 500));*/
                    this->_powerUpsId++;
                }
                this->_boxes.erase(boxFound);
                this->_map.setBoxes(this->_boxes);
                break;
            }

            auto const  &bonusFound = std::find_if(this->_bonuses.begin(), this->_bonuses.end(), f);
            if (bonusFound != this->_bonuses.end()) {
                this->_bonuses.erase(bonusFound);
            }
        }
    }
    auto    owner = this->_getOwner(bomb.getOwner());
    if (owner != this->_characters.end()) {
        std::cout << "INCCAP Owner : " << owner->getId() << std::endl;
        owner->incCap(1);
    }

    this->_bombs.erase(std::remove_if(this->_bombs.begin(), this->_bombs.end(),
                                      [&bomb](Bomb const &current) { return current.getId() == bomb.getId(); }));
}

Referee const &
Referee::update(bool const spawnPowerUps, int const value) {
    for (size_t i = 0; i < this->_bombs.size(); ++i) {
        if (static_cast<int>(this->_bombs[i].getTimer()) - value <= 0) {
            this->_detonate(this->_bombs[i], spawnPowerUps);
            i--;
        } else {
            this->_bombs[i].decTimer(value);
        }
    }
    for (size_t i = 0; i < this->_bonuses.size(); ++i) {
        if (static_cast<int>(this->_bonuses[i].getTimer()) - value <= 0) {
            this->_bonuses.erase(this->_bonuses.begin() + i);
            i--;
        } else {
            this->_bonuses[i].decTimer(value);
        }
    }
    return *this;
}

bool
Referee::isCellAvailable(irr::core::vector3df const &fPos) const {
    irr::core::vector3d<int> const      &iPos = this->_convertToInt(fPos);
    auto    f = [&iPos, this](auto const &elem) {
        return this->_convertToInt(elem.getPosition()) == iPos;
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
    return !(boxFound != this->_boxes.end());
}

irr::core::vector3d<int> const
Referee::_getBlast(irr::core::vector3d<int> const &pos, size_t const offset, Action::Type const &dir) const {
    switch (dir) {
        case Action::UP:
            return irr::core::vector3d<int>(pos.X, pos.Y, pos.Z - static_cast<int>(offset));

        case Action::RIGHT:
            return irr::core::vector3d<int>(pos.X + static_cast<int>(offset), pos.Y, pos.Z);

        case Action::DOWN:
            return irr::core::vector3d<int>(pos.X, pos.Y, pos.Z + static_cast<int>(offset));

        case Action::LEFT:
            return irr::core::vector3d<int>(pos.X - static_cast<int>(offset), pos.Y, pos.Z);

        default:
            break;
    }
    return pos;
}

void
Referee::_activatePowerUps(Character &player) {
    irr::core::vector3d<int> const &pos = this->_convertToInt(player.getPosition());

    auto const &bonusFound = std::find_if(this->_bonuses.begin(), this->_bonuses.end(),
                                          [&pos, this](auto const &elem) {
                                              return this->_convertToInt(elem.getPosition()) == pos;
                                          });
    if (bonusFound != this->_bonuses.end()) {
        std::cout << "FOUND POWERUP OF TYPE [";
        switch (bonusFound->getType()) {
            case AEntity::SPEED:
                std::cout << "SPEED]" << std::endl;
                if (player.getSpeed() < SPEED_LIMIT) {
                    player.incSpeed(SPEED_INC_UNIT);
                    player.incSpeedTaken(1);
                }
                break;

            case AEntity::STRENGTH:
                std::cout << "STRENGTH]" << std::endl;
                player.incPower(1);
                player.incPowerTaken(1);
                break;

            case AEntity::SHORTFUSE:
                std::cout << "SHORTFUSE]" << std::endl;
                if (player.getFuse() > FUSE_UNIT / 4) {
                    player.decFuse(player.getFuse() / 6);
                    player.incFuseTaken(1);
                }
                break;

            case AEntity::CAPACITY:
                std::cout << "CAPACITY]" << std::endl;
                player.incCap(1);
                player.incCapTaken(1);
                break;

            default:
                break;
        }
        player.incBonusTaken(1);
        this->_bonuses.erase(bonusFound);
    }
}

std::vector<Bomb> const & Referee::getBombs() const {
    return _bombs;
}

std::vector<PowerUp> const & Referee::getBonuses() const {
    return _bonuses;
}

std::vector<Character> const & Referee::getCharacters() const {
    return _characters;
}

irr::core::vector3d<int> const
Referee::_convertToInt(irr::core::vector3df const &origin) const {
    return irr::core::vector3d<int>(static_cast<int>(origin.X),
                                    static_cast<int>(origin.Y),
                                    static_cast<int>(origin.Z));
}


Map const &
Referee::getMap() const {
    return this->_map;
}

void Referee::clear() {
    _bombs.clear();
    _bonuses.clear();
    _characters.clear();
    _boxes.clear();
    _map.clearMap();
}