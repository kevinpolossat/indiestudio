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
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include "Error.hh"
#include "Map.hh"

Map::Map() : _distrib(0, MAP_CHANCE) {
}

Map::Map(std::string const &file) : _distrib(0, MAP_CHANCE) {
    this->loadFromFile(file);
}

Map::Map(Map const &other) : _distrib(0, MAP_CHANCE) {
    this->_cameraPOS = other._cameraPOS;
    this->_cameraDIR = other._cameraDIR;
    this->_boxes = other._boxes;
    this->_spawns = other._spawns;
    this->_walls = other._walls;
}

Map::~Map() {
}

Map& Map::operator=(Map const &other) {
    if (this != &other) {
      this->_cameraPOS = other._cameraPOS;
      this->_cameraDIR = other._cameraDIR;
      this->_spawns = other._spawns;
      this->_boxes = other._boxes;
      this->_walls = other._walls;
    }
    return *this;
}

void Map::saveToFile(std::string const &file) {
    std::ofstream ofs(file);
    if (!ofs.is_open())
        throw RuntimeError("Cannot open file", "saveToFile");
    boost::archive::text_oarchive oa(ofs, boost::archive::no_header);
    oa << *this;
    ofs.close();
}

void Map::loadFromFile(std::string const &file) {
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw RuntimeError("Cannot open file", "loadFromFile");
    boost::archive::text_iarchive ia(ifs, boost::archive::no_header);
    ia >> *this;
    auto it = this->_boxes.begin();
    while (it != this->_boxes.end()) {
        uint32_t rand = static_cast<uint32_t>(this->_distrib(this->_generator));
        if (!rand) {
            it = this->_boxes.erase(it);
        } else {
            it++;
        }
    }
    ifs.close();
}

void Map::clearMap() {
    this->_spawns.clear();
    this->_boxes.clear();
    this->_walls.clear();
}

irr::core::vector3df const& Map::getCameraPOS() const {
    return this->_cameraPOS;
}

irr::core::vector3df const& Map::getCameraDIR() const {
    return this->_cameraDIR;
}

std::vector<Cell> const &Map::getSpawns() const {
    return this->_spawns;
}

std::vector<Cell> &Map::getBoxes() {
    return this->_boxes;
}

std::vector<Cell> const &Map::getBoxes() const {
    return this->_boxes;
}

std::vector<Cell> const &Map::getWalls() const {
    return this->_walls;
}

void Map::setCameraPOS(const irr::core::vector3df &pos) {
    this->_cameraPOS = pos;
}

void Map::setCameraDIR(const irr::core::vector3df &dir) {
    this->_cameraDIR = dir;
}

void Map::setSpawns(std::vector<Cell> const &spawns) {
    this->_spawns = spawns;
}

void Map::setBoxes(std::vector<Cell> const &boxes) {
    this->_boxes = boxes;
}

void Map::setWalls(std::vector<Cell> const &walls) {
    this->_walls = walls;
}

//TODO: DELETE BELOW CODE
/*#include <irrlicht.h>
int main()
{
   //0 = wall
   //1 = box
   //2 = empty
   //3 = spawn
   const int size_width = 15;
   const int size_height = 13;
   static const int var[size_height][size_width] = { // Best code ever
           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
           {0, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 0},
           {0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0},
	   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
           {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
           {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
           {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	   {0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0},
	   {0, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   };
   Map map;
   std::vector<Cell> walls;
   std::vector<Cell> boxes;
   std::vector<Cell> spawns;
   irr::s32 id = 0;

   for (int y = 0; y < size_height; y++) {
       for (int x = 0; x < size_width; x++) {
           switch (var[y][x]) {
               case 0:
                   walls.push_back(Cell(irr::core::vector3df(x, 1, y), irr::core::vector3df(0, 0, 0), "DefaultWall"));
                   break;
               case 1:
                   walls.push_back(Cell(irr::core::vector3df(x, 0, y), irr::core::vector3df(0, 0, 0), "DefaultGround"));
                   boxes.push_back(Cell(irr::core::vector3df(x, 1, y), irr::core::vector3df(0, 0, 0), "DefaultBox", ++id));
                   break;
               case 2:
                   walls.push_back(Cell(irr::core::vector3df(x, 0, y), irr::core::vector3df(0, 0, 0), "DefaultGround"));
                   break;
               case 3:
                   walls.push_back(Cell(irr::core::vector3df(x, 0, y), irr::core::vector3df(0, 0, 0), "DefaultGround"));
                   spawns.push_back(Cell(irr::core::vector3df(x + .5f, 1, y + .5f), irr::core::vector3df(0, 0, 0), ""));
                   break;
               default:
                   continue;
           }
       }
   }

   map.setCameraPOS(irr::core::vector3df(0, 0, 0));
   map.setCameraDIR(irr::core::vector3df(0, 0, 0));
   map.setWalls(walls);
   map.setBoxes(boxes);
   map.setSpawns(spawns);
   map.saveToFile("Basic.map");
   }*/
/*#include <iostream>
int main() {
    Map map("Basic.map");

    std::cout << map.getSpawns().size() << std::endl; //Must be 4
    std::cout << map.getBoxes().size() << std::endl; //Must be 263
    std::cout << map.getWalls().size() << std::endl; //Must be 437
}*/

