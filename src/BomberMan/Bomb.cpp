//
// Created by beurie_v on 16/05/17.
//

#include "Bomb.hh"

Bomb::Bomb() {
}

Bomb::Bomb(irr::core::vector3d<int> const &pos, uint32_t const id,
           uint32_t const timer, uint32_t const power, uint32_t const owner)
        : AEntity(irr::core::vector3df(pos.X, pos.Y, pos.Z)),
          _id(id),
          _timer(timer),
          _power(power),
          _owner(owner),
          _isExploding(false) {

}

Bomb::Bomb(Bomb const &other)
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _timer(other._timer),
          _power(other._power),
          _owner(other._owner),
          _isExploding(other._isExploding) {

}

Bomb::Bomb(Bomb &&other)
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _timer(other._timer),
          _power(other._power),
          _owner(other._owner),
          _isExploding(other._isExploding) {

}

Bomb::~Bomb() {

}

Bomb &
Bomb::operator=(Bomb const &other) {
    if (&other != this) {
        this->_owner = other._owner;
        this->_id = other._id;
        this->_x = other._x;
        this->_y = other._y;
        this->_z = other._z;
        this->_power = other._power;
        this->_timer = other._timer;
        this->_isExploding = other._isExploding;
    }
    return *this;
}

irr::s32
Bomb::getId() const {
    return this->_id;
}

uint32_t
Bomb::getTimer() const {
    return this->_timer;
}

uint32_t
Bomb::getPower() const {
    return this->_power;
}

uint32_t
Bomb::getOwner() const {
    return this->_owner;
}

bool
Bomb::getState() const {
    return this->_isExploding;
}

void
Bomb::decTimer(int const value) {
    this->_timer -= value;
}

void
Bomb::setState(bool const state) {
    this->_isExploding = state;
}
