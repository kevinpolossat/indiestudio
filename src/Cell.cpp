/*
** Cell.cpp for cpp in /home/lecler_2/delivery/cpp/Cell.cpp
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed May 10 15:32:21 2017 Mickaël Leclerc
** Last update Wed May 10 15:32:21 2017 Mickaël Leclerc
*/

#include "Cell.hh"

Cell::Cell() {
}

Cell::Cell(irr::core::vector3df const &position, irr::core::vector3df const &rotation, std::string const &mesh, irr::s32 id) {
    this->_id = id;
    this->_position = position;
    this->_rotation = rotation;
    this->_mesh = mesh;
}

Cell::Cell(Cell const &other) {
    this->_id = other._id;
    this->_position = other._position;
    this->_rotation = other._rotation;
    this->_mesh = other._mesh;
}

Cell::Cell(Cell && other) {
    this->_id       = other._id;
    this->_position = other._position;
    this->_rotation = other._rotation;
    this->_mesh     = other._mesh;
}

Cell& Cell::operator=(Cell const &other) {
    if (this != &other) {
        this->_id = other._id;
        this->_position = other._position;
        this->_rotation = other._rotation;
        this->_mesh = other._mesh;
    }
    return *this;
}

Cell::~Cell() {
}

irr::s32			       Cell::getId() const {
    return this->_id;
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
