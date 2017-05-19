//
// Created by beurie_v on 16/05/17.
//

#include "Bomb.hh"

Bomb::Bomb(irr::core::vector3df const &pos, uint32_t const &id,
           uint32_t const &timer, uint32_t const &power, uint32_t const &owner)
        : AEntity(pos),
          _id(id),
          _timer(timer),
          _power(power),
          _owner(owner) {

}

Bomb::Bomb(Bomb const &other)
        : AEntity(other._position),
          _id(other._id),
          _timer(other._timer),
          _power(other._power),
          _owner(other._owner) {

}

Bomb::Bomb(Bomb &&other)
        : AEntity(other._position),
          _id(other._id),
          _timer(other._timer),
          _power(other._power),
          _owner(other._owner) {

}

Bomb::~Bomb() {

}

Bomb &
Bomb::operator=(Bomb const &other) {
    if (&other != this) {
        this->_owner = other._owner;
        this->_id = other._id;
        this->_position = other._position;
        this->_power = other._power;
        this->_timer = other._timer;
    }
    return *this;
}

uint32_t const &
Bomb::getId() const {
    return this->_id;
}

uint32_t const &
Bomb::getTimer() const {
    return this->_timer;
}

uint32_t const &
Bomb::getPower() const {
    return this->_power;
}

uint32_t const &
Bomb::getOwner() const {
    return this->_owner;
}

void
Bomb::decTimer() {
    this->_timer--;
}
