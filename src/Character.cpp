//
// Created by beurie_v on 17/05/17.
//

#include "Character.hh"

Character::Character(uint32_t const &id, irr::core::vector3df const &pos)
        : AEntity(pos),
          _id(id),
          _speed(1),
          _capacity(1),
          _power(3),
          _fuse(10) {

}

Character::~Character() {

}

uint32_t const &
Character::getId() const {
    return this->_id;
}

uint32_t const &
Character::getSpeed() const {
    return this->_speed;
}

uint32_t const &
Character::getCapacity() const {
    return this->_capacity;
}

uint32_t const &
Character::getPower() const {
    return this->_power;
}

uint32_t const &
Character::getFuse() const {
    return this->_fuse;
}

void
Character::incCap(uint32_t const &value) {
    this->_capacity += value;
}

void
Character::decCap(uint32_t const &value) {
    this->_capacity -= value;
}

void
Character::incSpeed(uint32_t const &value) {
    this->_speed += value;
}

void
Character::decSpeed(uint32_t const &value) {
    this->_speed -= value;
}

void
Character::incPower(uint32_t const &value) {
    this->_power += value;
}

void
Character::decPower(uint32_t const &value) {
    this->_power -= value;
}

void
Character::incFuse(uint32_t const &value) {
    this->_fuse += value;
}

void
Character::decFuse(uint32_t const &value) {
    this->_fuse -= value;
}
