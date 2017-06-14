//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_BOMB_HH
#define CPP_BOMB_HH

#include <cstdint>
#include "AEntity.hh"

class          Bomb : public AEntity {
private:
    irr::s32    _id;
    uint32_t    _timer;
    uint32_t    _power;
    uint32_t    _owner;
    bool        _isExploding;

public:
    Bomb();
    explicit Bomb(irr::core::vector3d<int> const &, uint32_t const,
                  uint32_t const, uint32_t const, uint32_t const);
    Bomb(Bomb const &);
    Bomb(Bomb &&);
    virtual ~Bomb();

    Bomb            &operator=(Bomb const &);

    irr::s32 getId()     const;
    uint32_t getTimer()  const;
    uint32_t getPower()  const;
    uint32_t getOwner()  const;
    bool    getState() const;

    void            decTimer(int const);
    void            setState(bool const);
};


#endif //CPP_BOMB_HH
