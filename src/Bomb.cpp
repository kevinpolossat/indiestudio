//
// Created by beurie_v on 16/05/17.
//

#include "Bomb.hh"

Bomb::Bomb(irr::core::vector3df const &pos, uint32_t const &timer,
           uint32_t const &power, uint32_t const &owner)
        : AEntity(pos),
          _timer(timer),
          _power(power),
          _owner(owner) {

}

Bomb::~Bomb() {

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
