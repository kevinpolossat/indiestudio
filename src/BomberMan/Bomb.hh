//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_BOMB_HH
#define CPP_BOMB_HH

#include <cstdint>
#include "AEntity.hh"

class          Bomb : public AEntity {
private:
    uint32_t    _id;
    uint32_t    _timer;
    uint32_t    _power;
    uint32_t    _owner;

public:
    Bomb() = delete;
    explicit Bomb(irr::core::vector3df const &, uint32_t const,
                  uint32_t const, uint32_t const, uint32_t const);
    Bomb(Bomb const &);
    Bomb(Bomb &&);
    virtual ~Bomb();

    Bomb            &operator=(Bomb const &);

    uint32_t getId()     const;
    uint32_t getTimer()  const;
    uint32_t getPower()  const;
    uint32_t getOwner()  const;

    void            decTimer();
};


#endif //CPP_BOMB_HH
