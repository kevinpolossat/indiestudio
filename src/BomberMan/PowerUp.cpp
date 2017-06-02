//
// Created by beurie_v on 16/05/17.
//

#include "PowerUp.hh"
#include "Action.hh"

PowerUp::PowerUp(irr::core::vector3d<int> const &pos, uint32_t const id,
                 AEntity::PowerUpType const &type, uint32_t const timer)
        : AEntity(irr::core::vector3df(pos.X, pos.Y, pos.Z)),
          _id(id),
          _type(type),
          _timer(timer) {
    std::string    tab[4] = { "SPEED", "STRENGTH", "SHORTFUSE", "CAPACITY"};

    std::cout << "Created PowerUp of type [" << tab[type] << "], pos = " << pos.X << ", " << pos.Y << ", " << pos.Z << std::endl;
}

PowerUp::PowerUp(PowerUp const &other)
        : AEntity(other._position),
          _id(other._id),
          _type(other._type),
          _timer(other._timer) {

}

PowerUp::PowerUp(PowerUp &&other)
        : AEntity(other._position),
          _id(other._id),
          _type(other._type),
          _timer(other._timer) {

}

PowerUp::~PowerUp() {

}

PowerUp &
PowerUp::operator=(PowerUp const &other) {
    if (&other != this) {
        this->_position = other._position;
        this->_id = other._id;
        this->_type = other._type;
        this->_timer = other._timer;
    }
    return *this;
}

void PowerUp::decTimer() {
    this->_timer--;
}

uint32_t const
PowerUp::getId() const {
    return this->_id;
}

const AEntity::PowerUpType &
PowerUp::getType() const {
    return this->_type;
}

const uint32_t
PowerUp::getTimer() const {
    return this->_timer;
}


