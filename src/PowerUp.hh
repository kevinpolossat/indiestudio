//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_POWERUP_HH
#define CPP_POWERUP_HH


#include "AEntity.hh"
#include "Game.hh"

class           PowerUp : public AEntity {
private:
    AEntity::PowerUpType       _type;
    uint32_t                   _timer;

public:
    PowerUp() = delete;
    explicit PowerUp(irr::core::vector3df const &, AEntity::PowerUpType const &,
                     uint32_t const &);
    PowerUp(PowerUp &&) = delete;
    PowerUp(PowerUp const &) = delete;
    virtual ~PowerUp();

    PowerUp                         &operator=(PowerUp const &) = delete;

    void                            decTimer();

    AEntity::PowerUpType const     &getType() const;
    uint32_t const                 &getTimer() const;

};


#endif //CPP_POWERUP_HH
