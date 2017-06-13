//
// Created by beurie_v on 17/05/17.
//

#include "Character.hh"

Character::Character(uint32_t const id, irr::core::vector3df const &pos)
        : AEntity(pos),
          _id(id),
          _speed(SPEED_MLTPLIER),
          _capacity(BOMB_CAPACITY),
          _power(BOMB_POWER),
          _fuse(FUSE_UNIT),
          _bonusTaken(0),
          _capTaken(0),
          _fuseTaken(0),
          _powerTaken(0),
          _speedTaken(0) {

}

Character::Character(Character const &other)
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _speed(other._speed),
          _capacity(other._capacity),
          _power(other._power),
          _fuse(other._fuse),
          _bonusTaken(other._bonusTaken),
          _capTaken(other._capTaken),
          _fuseTaken(other._fuseTaken),
          _powerTaken(other._powerTaken),
          _speedTaken(other._speedTaken) {

}

Character::Character(Character &&other)
        : AEntity(irr::core::vector3df(other._x, other._y, other._z)),
          _id(other._id),
          _speed(other._speed),
          _capacity(other._capacity),
          _power(other._power),
          _fuse(other._fuse),
          _bonusTaken(other._bonusTaken),
          _capTaken(other._capTaken),
          _fuseTaken(other._fuseTaken),
          _powerTaken(other._powerTaken),
          _speedTaken(other._speedTaken) {

}

Character::~Character() {

}

Character &
Character::operator=(Character const &other) {
    if (&other != this) {
        this->_x = other._x;
        this->_y = other._y;
        this->_z = other._z;
        this->_id = other._id;
        this->_speed = other._speed;
        this->_capacity = other._capacity;
        this->_power = other._power;
        this->_fuse = other._fuse;
        this->_bonusTaken = other._bonusTaken;
        this->_capTaken = other._capTaken;
        this->_fuseTaken = other._fuseTaken;
        this->_powerTaken = other._powerTaken;
        this->_speedTaken = other._speedTaken;
    }
    return *this;
}

uint32_t
Character::getId() const {
    return this->_id;
}

float
Character::getSpeed() const {
    return this->_speed;
}

uint32_t
Character::getCapacity() const {
    return this->_capacity;
}

uint32_t
Character::getPower() const {
    return this->_power;
}

uint32_t
Character::getFuse() const {
    return this->_fuse;
}

uint32_t Character::getBonusTaken() const {
    return this->_bonusTaken;
}

void
Character::incCap(uint32_t const value) {
    this->_capacity += value;
}

void
Character::decCap(uint32_t const value) {
    this->_capacity -= value;
}

void
Character::incSpeed(float const value) {
    this->_speed += value;
}

void
Character::decSpeed(float const value) {
    this->_speed -= value;
}

void
Character::incPower(uint32_t const value) {
    this->_power += value;
}

void
Character::decPower(uint32_t const value) {
    this->_power -= value;
}

void
Character::incFuse(uint32_t const value) {
    this->_fuse += value;
}

void
Character::decFuse(uint32_t const value) {
    this->_fuse -= value;
}

void
Character::incBonusTaken(uint32_t const value) {
    this->_bonusTaken += value;
}

void
Character::decBonusTaken(uint32_t const value) {
    this->_bonusTaken -= value;
}

uint32_t
Character::getCapTaken() const {
    return this->_capTaken;
}

uint32_t
Character::getFuseTaken() const {
    return this->_fuseTaken;
}

uint32_t
Character::getPowerTaken() const {
    return this->_powerTaken;
}

uint32_t
Character::getSpeedTaken() const {
    return this->_speedTaken;
}

void
Character::incCapTaken(uint32_t const value) {
    this->_capTaken += value;
}

void
Character::incFuseTaken(uint32_t const value) {
    this->_fuseTaken += value;
}

void
Character::incPowerTaken(uint32_t const value) {
    this->_powerTaken += value;
}

void
Character::incSpeedTaken(uint32_t const value) {
    this->_speedTaken += value;
}
