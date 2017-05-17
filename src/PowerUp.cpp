//
// Created by beurie_v on 16/05/17.
//

#include "PowerUp.hh"

PowerUp::PowerUp(irr::core::vector3df const &pos, AEntity::PowerUpType const &type,
                 uint32_t const &timer)
        : AEntity(pos),
          _type(type),
          _timer(timer) {

}

PowerUp::~PowerUp() {

}

void PowerUp::decTimer() {
    this->_timer--;
}

const AEntity::PowerUpType &
PowerUp::getType() const {
    return this->_type;
}

const uint32_t &
PowerUp::getTimer() const {
    return this->_timer;
}
