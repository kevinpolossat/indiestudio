//
// Created by beurie_v on 17/05/17.
//

#ifndef CPP_CHARACTERS_HH
#define CPP_CHARACTERS_HH


#include "AEntity.hh"
#include "PowerUp.hh"

class       Character : public AEntity {
private:
    uint32_t            _id;
    uint32_t            _speed;
    uint32_t            _capacity;
    uint32_t            _power;
    uint32_t            _fuse;

public:
    Character() = delete;
    explicit Character(uint32_t const &, irr::core::vector3df const &);
    Character(Character const &);
    Character(Character &&);
    virtual ~Character();

    Character          &operator=(Character const &);

    uint32_t const     &getId() const;
    uint32_t const     &getSpeed() const;
    uint32_t const     &getCapacity() const;
    uint32_t const     &getPower() const;
    uint32_t const     &getFuse() const;

    void               incCap(uint32_t const &);
    void               decCap(uint32_t const &);
    void               incSpeed(uint32_t const &);
    void               decSpeed(uint32_t const &);
    void               incPower(uint32_t const &);
    void               decPower(uint32_t const &);
    void               incFuse(uint32_t const &);
    void               decFuse(uint32_t const &);
};


#endif //CPP_CHARACTERS_HH
