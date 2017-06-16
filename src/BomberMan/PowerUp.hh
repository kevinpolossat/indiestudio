//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_POWERUP_HH
#define CPP_POWERUP_HH


#include "AEntity.hh"
#include "Game.hh"

class           PowerUp : public AEntity {
private:
    irr::s32                   _id;
    AEntity::PowerUpType       _type;
    uint32_t                   _timer;

public:
    PowerUp();
    explicit PowerUp(irr::core::vector3d<int> const &, uint32_t const,
                     AEntity::PowerUpType const &, uint32_t const);
    PowerUp(PowerUp const &);
    PowerUp(PowerUp &&);
    virtual ~PowerUp();

    PowerUp                         &operator=(PowerUp const &);

    void                            decTimer(int const);

    irr::s32                        getId() const;
    AEntity::PowerUpType const      &getType() const;
    uint32_t                        getTimer() const;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & this->_x;
        ar & this->_y;
        ar & this->_z;
        ar & this->_id;
        ar & this->_type;
        ar & this->_timer;
    }
};


#endif //CPP_POWERUP_HH
