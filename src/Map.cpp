/*
** Map.cpp for cpp in /home/lecler_2/delivery/cpp/Map.cpp
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed May 10 15:59:42 2017 Mickaël Leclerc
** Last update Wed May 10 15:59:42 2017 Mickaël Leclerc
*/

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include "Map.hh"

Map::Map() {
}

Map::Map(std::string const &file) {
    this->loadFromFile(file);
}

Map::~Map() {
}

bool Map::loadFromFile(std::string const &file) {
    std::ifstream ifs(file);
    if (ifs.is_open()) {
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
        ifs.close();
        return true;
    }
    return false;
}

void Map::clearMap() {
    this->_spawns.clear();
    this->_boxes.clear();
    this->_walls.clear();
}

std::vector<Cell>   const& Map::getSpawns() const {
    return this->_spawns;
}

std::vector<Cell>   & Map::getBoxes() {
    return this->_boxes;
}

std::vector<Cell>   const& Map::getBoxes() const {
    return this->_boxes;
}

std::vector<Cell>   const& Map::getWalls() const {
    return this->_walls;
}