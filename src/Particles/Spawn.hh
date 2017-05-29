//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_SPAWN_HH
#define INDIESTUDIO_SPAWN_HH


class Spawn {
public:
    Spawn();
    Spawn(Spawn const & other)              = delete;
    Spawn(Spawn && other)                   = delete;
    Spawn & operator = (Spawn const other)  = delete;

    ~Spawn();
};


#endif //INDIESTUDIO_SPAWN_HH
