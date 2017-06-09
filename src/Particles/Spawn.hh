//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_SPAWN_HH
#define INDIESTUDIO_SPAWN_HH

#include <memory>

#include "irrlicht.h"

class Spawn {
public:
    Spawn(irr::core::vector3df const & pos);
    Spawn(Spawn const & other)              = delete;
    Spawn(Spawn && other)                   = delete;
    Spawn & operator = (Spawn const other)  = delete;

    ~Spawn();
private:
    std::shared_ptr<irr::scene::IVolumeLightSceneNode> _ln;
};


#endif //INDIESTUDIO_SPAWN_HH
