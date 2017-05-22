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
    Map &operator=(Map const&);
    virtual ~Map();

    /**
     * Save object from class to XML file
     * @param file name
     */
    void                saveToFile(std::string const& file);

    /**
     * Load object into class of the XML file
     * @param file name
     */
    void                loadFromFile(std::string const& file);

    /**
     * Clear all object of class
     */
    void                clearMap(void);

    /**
     * Different getter of attributes
     */
    std::vector<Cell>   const& getSpawns(void) const;
    std::vector<Cell>   & getBoxes(void);
    std::vector<Cell>   const& getBoxes(void) const;
    std::vector<Cell>   const& getWalls(void) const;

    /**
     * Different setter of attributes
     */
    void                setSpawns(std::vector<Cell> const& spawns);
    void                setBoxes(std::vector<Cell> const& boxes);
    void                setWalls(std::vector<Cell> const& walls);

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
