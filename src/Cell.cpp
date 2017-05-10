/*
** Cell.cpp for cpp in /home/lecler_2/delivery/cpp/Cell.cpp
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed May 10 15:32:21 2017 Mickaël Leclerc
** Last update Wed May 10 15:32:21 2017 Mickaël Leclerc
*/

#include <irrlicht.h>
#include <string>
#include "Cell.hh"

Cell::Cell() {
}

Cell::Cell(irr::core::vector3df const &position, irr::core::vector3df const &rotation, std::string const &mesh) {
    this->_position = position;
    this->_rotation = rotation;
    this->_mesh = mesh;
}

Cell::Cell(Cell const &other) {
    this->_position = other._position;
    this->_rotation = other._rotation;
    this->_mesh = other._mesh;
}

Cell::~Cell() {
}

irr::core::vector3df    const& Cell::getPosition() const {
    return this->_position;
}

irr::core::vector3df    const& Cell::getRotation() const {
    return this->_rotation;
}

std::string             const& Cell::getMesh() const {
    return this->_mesh;
}