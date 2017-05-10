/*
** Cell.hh for cpp in /home/lecler_2/delivery/cpp/Cell.hh
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed May 10 14:56:21 2017 Mickaël Leclerc
** Last update Wed May 10 14:56:21 2017 Mickaël Leclerc
*/
#ifndef CPP_CELL_HH
#define CPP_CELL_HH

#include <boost/serialization/string.hpp>
#include <irrlicht.h>
#include <string>

/**
 * Cell representation. Used for blocks, walls, boxes, spawn, etc..
 */
class Cell {
public:
    Cell();
    Cell(irr::core::vector3df const& position, irr::core::vector3df const& rotation, std::string const& mesh);
    Cell(Cell const&);
    Cell &operator=(Cell const&) = delete;
    virtual ~Cell();

    /**
     * Getter for position
     * @return position
     */
    irr::core::vector3df    const& getPosition(void) const;

    /**
     * Getter for rotation
     * @return rotation
     */
    irr::core::vector3df    const& getRotation(void) const;

    /**
     * Getter for mesh name
     * @return mesh name
     */
    std::string             const& getMesh(void) const;

    /**
     * Method used for XML serialization
     * @tparam Archive
     * @param ar
     */
    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & this->_position.X;
        ar & this->_position.Y;
        ar & this->_position.Z;

        ar & this->_rotation.X;
        ar & this->_rotation.Y;
        ar & this->_rotation.Z;

        ar & this->_mesh;
    }

private:
    irr::core::vector3df    _position;
    irr::core::vector3df    _rotation;
    std::string             _mesh;
};

#endif //CPP_CELL_HH