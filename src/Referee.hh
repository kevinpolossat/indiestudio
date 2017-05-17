//
// Created by beurie_v on 17/05/17.
//

#ifndef CPP_REFEREE_HH
#define CPP_REFEREE_HH

#include <iostream>
#include <vector>
#include "Bomb.hh"
#include "PowerUp.hh"
#include "Character.hh"
#include "Map.hh"

class       Referee {
private:
    std::vector<Bomb>            _bombs;
    std::vector<Character>       _characters;
    std::vector<PowerUp>         _bonuses;

public:
    Referee() = delete;
    Referee(uint32_t const &, Map const &);
    explicit Referee(Referee const &);
    Referee(Referee &&) = delete;
    ~Referee();

    Referee         &operator=(Referee const &) = delete;
};


#endif //CPP_REFEREE_HH
