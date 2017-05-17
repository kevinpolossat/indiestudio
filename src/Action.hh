//
// Created by kevin on 17/05/17.
//

#ifndef INDIESTUDIO_ACTION_HH
#define INDIESTUDIO_ACTION_HH

#include <cstdint>
#include <boost/serialization/vector.hpp>

class Action {
public:
    using Id = int;
    enum Type {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        BOMB
    };
private:
    Type    _type;
    Id      _id;
public:
    explicit Action(int id, Type t);
    ~Action();

    Action(Action const & other);
    Action(Action && other);
    Action & operator=(Action const & other);

    Type    type() const;
    Id      id() const;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & _type;
        ar & _id;
    }
};


#endif //INDIESTUDIO_ACTION_HH
