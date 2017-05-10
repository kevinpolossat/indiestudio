/*
** Map.hh for cpp in /home/lecler_2/delivery/cpp/Map.hh
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed May 10 15:46:21 2017 Mickaël Leclerc
** Last update Wed May 10 15:46:21 2017 Mickaël Leclerc
*/
#ifndef CPP_MAP_HH
#define CPP_MAP_HH

#include <boost/serialization/vector.hpp>
#include <memory>
#include <vector>
#include "Cell.hh"

/**
 * Map representation. Can load from a XML file and store walls, boxes and spawn
 */
class Map {
public:
    Map();
    Map(std::string const& file);
    Map(Map const&) = delete;
    Map &operator=(Map const&) = delete;
    virtual ~Map();

    /**
     * Load object into class of the XML file
     * @param file name
     * @return success or failure
     */
    bool                loadFromFile(std::string const& file);

    /**
     * Clear all object of class
     */
    void                clearMap(void);

    /**
     * Getter for spawn
     * @return spawns cells
     */
    std::vector<Cell>   const& getSpawns(void) const;

    /**
     * Getter for boxes. Non const because they can be destroyed by bomb explosions
     * @return boxes cells
     */
    std::vector<Cell>   & getBoxes(void);
    std::vector<Cell>   const& getBoxes(void) const;

    /**
     * Getter for walls
     * @return walls cells
     */
    std::vector<Cell>   const& getWalls(void) const;

    /**
     * Method used for XML serialization
     * @tparam Archive
     * @param ar
     */
    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & this->_spawns;
        ar & this->_boxes;
        ar & this->_walls;
    }

private:
    std::vector<Cell>   _spawns;
    std::vector<Cell>   _boxes;
    std::vector<Cell>   _walls;
};

#endif //CPP_MAP_HH
