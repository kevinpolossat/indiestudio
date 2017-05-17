//
// Created by beurie_v on 16/05/17.
//

#include "AEntity.hh"

AEntity::AEntity(irr::core::vector3df const &position)
        : _position(position) {

}

AEntity::~AEntity() {

}

void
AEntity::setPosition(irr::core::vector3df const &pos) {
    this->_position = pos;
}

irr::core::vector3df const &
AEntity::getPosition() const {
    return this->_position;
}

