//
// Created by beurie_v on 16/05/17.
//

#ifndef CPP_AENTITY_HH
#define CPP_AENTITY_HH

#include <irrlicht.h>

class           AEntity {
protected:
    float       _x;
    float       _y;
    float       _z;
    AEntity(irr::core::vector3df const &);

public:
    enum PowerUpType { SPEED = 0, STRENGTH, SHORTFUSE, CAPACITY };

    AEntity();
    AEntity(AEntity const &) = delete;
    AEntity(AEntity &&) = delete;

    virtual ~AEntity();

    AEntity                     &operator=(AEntity const &) = delete;

    void                        setPosition(irr::core::vector3df const &);
    irr::core::vector3df const  getPosition() const;
};


#endif //CPP_AENTITY_HH
