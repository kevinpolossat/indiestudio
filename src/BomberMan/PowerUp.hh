//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_POWERUP_HH
#define CPP_POWERUP_HH


#include "AEntity.hh"
#include "Game.hh"

class           PowerUp : public AEntity {
private:
    uint32_t                   _id;
    AEntity::PowerUpType       _type;
    uint32_t                   _timer;

public:
    PowerUp() = delete;
    explicit PowerUp(irr::core::vector3d<int> const &, uint32_t const,
                     AEntity::PowerUpType const &, uint32_t const);
    PowerUp(PowerUp const &);
    PowerUp(PowerUp &&);
    virtual ~PowerUp();

    PowerUp                         &operator=(PowerUp const &);

    void                            decTimer();

    uint32_t                        getId() const;
    AEntity::PowerUpType const      &getType() const;
    uint32_t                        getTimer() const;

};


#endif //CPP_POWERUP_HH
