//
// Created by beurie_v on 16/05/17.
//

#include "PowerUp.hh"
#include "Action.hh"

PowerUp::PowerUp() {
}

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
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _type(other._type),
          _timer(other._timer) {

}

PowerUp::PowerUp(PowerUp &&other)
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _type(other._type),
          _timer(other._timer) {

}

PowerUp::~PowerUp() {

}

PowerUp &
PowerUp::operator=(PowerUp const &other) {
    if (&other != this) {
        this->_x = other._x;
        this->_y = other._y;
        this->_z = other._z;
        this->_id = other._id;
        this->_type = other._type;
        this->_timer = other._timer;
    }
    return *this;
}

void PowerUp::decTimer() {
    this->_timer--;
}

irr::s32
PowerUp::getId() const {
    return this->_id;
}

const AEntity::PowerUpType &
PowerUp::getType() const {
    return this->_type;
}

uint32_t
PowerUp::getTimer() const {
    return this->_timer;
}


