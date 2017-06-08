//
// Created by beurie_v on 16/05/17.
//

#include "AEntity.hh"

AEntity::AEntity(irr::core::vector3df const &position)
        : _x(position.X),
          _y(position.Y),
          _z(position.Z) {

}

AEntity::~AEntity() {

}

void
AEntity::setPosition(irr::core::vector3df const &pos) {
    this->_x = pos.X;
    this->_y = pos.Y;
    this->_z = pos.Z;
}

irr::core::vector3df const
AEntity::getPosition() const {
    return irr::core::vector3df(this->_x, this->_y, this->_z);
}

