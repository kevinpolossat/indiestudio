//
// Created by kevin on 17/05/17.
//

#ifndef INDIESTUDIO_ACTION_HH
#define INDIESTUDIO_ACTION_HH

#include <cstdint>

class Action {
public:
    using Id = int;
    enum Type {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
        BOMB,
        WAIT
    };
private:
    Type    _type;
    Id      _id;
    float   _speed;
public:
    explicit Action(int id, Type t, float speed);
    ~Action();

    Action(Action const & other);
    Action(Action && other);
    Action & operator=(Action const & other);

    Type    type()  const;
    Id      id()    const;
    float   speed() const;
};


#endif //INDIESTUDIO_ACTION_HH
