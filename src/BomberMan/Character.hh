//
// Created by beurie_v on 17/05/17.
//

#ifndef CPP_CHARACTERS_HH
#define CPP_CHARACTERS_HH

#include "AEntity.hh"
#include "PowerUp.hh"

#define SPEED_UNIT 0.05f
#define FUSE_UNIT 200

class       Character : public AEntity {
private:
    uint32_t            _id;
    float               _speed;
    uint32_t            _capacity;
    uint32_t            _power;
    uint32_t            _fuse;

public:
    Character();
    explicit Character(uint32_t const, irr::core::vector3df const &);
    Character(Character const &);
    Character(Character &&);
    virtual ~Character();

    Character          &operator=(Character const &);

    uint32_t           getId() const;
    float             getSpeed() const;
    uint32_t           getCapacity() const;
    uint32_t           getPower() const;
    uint32_t           getFuse() const;

    void               incCap(uint32_t const);
    void               decCap(uint32_t const);
    void               incSpeed(float const);
    void               decSpeed(float const);
    void               incPower(uint32_t const);
    void               decPower(uint32_t const);
    void               incFuse(uint32_t const);
    void               decFuse(uint32_t const);

    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & _x;
        ar & _y;
        ar & _z;
        ar & _id;
        ar & _speed;
        ar & _capacity;
        ar & _power;
        ar & _fuse;
    }
};


#endif //CPP_CHARACTERS_HH
