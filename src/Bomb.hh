//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_BOMB_HH
#define CPP_BOMB_HH

#include <cstdint>
#include "AEntity.hh"

class          Bomb : public AEntity {
private:
    uint32_t    _timer;
    uint32_t    _power;
    uint32_t    _owner;

public:
    Bomb() = delete;
    explicit Bomb(irr::core::vector3df const &, uint32_t const &,
                  uint32_t const &, uint32_t const &);
    Bomb(Bomb &&) = delete;
    Bomb(Bomb const &) = delete;
    virtual ~Bomb();

    Bomb            &operator=(Bomb const &) = delete;

    uint32_t const  &getTimer() const;
    uint32_t const  &getPower() const;
    uint32_t const  &getOwner() const;

    void            decTimer();
};


#endif //CPP_BOMB_HH
