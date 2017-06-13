//
// Created by beurie_v on 17/05/17.
//

#ifndef CPP_REFEREE_HH
#define CPP_REFEREE_HH

#include <boost/serialization/array.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include "Bomb.hh"
#include "PowerUp.hh"
#include "Character.hh"
#include "Map.hh"
#include "Action.hh"
#include "Error.hh"


class       Referee {
private:
    Map                                 _map;
    uint32_t                            _playerNbr;
    uint32_t                            _bombsId;
    uint32_t                            _powerUpsId;
    std::vector<Cell>                   _boxes;
    uint32_t                            _dropRate;
    std::uniform_int_distribution<int>  _distrib100;
    std::uniform_int_distribution<int>  _distrib4;
    std::vector<Bomb>                   _bombs;
    std::vector<PowerUp>                _bonuses;
    std::vector<Character>              _characters;
    std::default_random_engine          _generator;

    void                                _placeBomb(Character &);
    void                                _detonate(Bomb &, bool const);
    void                                _move(Character &, Action::Type const &, float const);
    std::vector<Character>::iterator    _getOwner(uint32_t const);
    irr::core::vector3d<int> const      _getBlast(irr::core::vector3d<int> const &, size_t const,
                                                  Action::Type const &) const;
    void                                _activatePowerUps(Character &);
    irr::core::vector3d<int> const      _convertToInt(irr::core::vector3df const &) const;

public:
    enum    MapCell {
        EMPTY = 0,
        WALL,
        BOX,
        BOMB,
        PSPEED,
        PSTRENGTH,
        PSHORTFUSE,
        PCAPACITY
    };
    Referee() = delete;
    explicit Referee(Map &, uint32_t const);
    explicit Referee(Referee const &);
    Referee(Referee &&) = delete;
    ~Referee();

    std::vector<Bomb> const & getBombs() const;
    std::vector<PowerUp> const & getBonuses() const;
    std::vector<Character> const & getCharacters() const;
    Map const & getMap() const;

    Referee         &operator=(Referee const &);

    void            doAction(uint32_t const, Action::Type const &, float const);
    void            clear();
    std::array<Referee::MapCell, 15 * 13>       refereeToArray() const;
    Referee const   &update(bool const, int const);
    bool            isCellAvailable(irr::core::vector3df const &) const;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & _map;
        ar & _playerNbr;
        ar & _bombsId;
        ar & _powerUpsId;
        ar & _boxes;
        ar & _dropRate;
        ar & _bombs;
        ar & _bonuses;
        ar & _characters;
    }
};


#endif //CPP_REFEREE_HH
