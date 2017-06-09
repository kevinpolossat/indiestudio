//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_SPAWN_HH
#define INDIESTUDIO_SPAWN_HH

#include <memory>

#include "irrlicht.h"
#include "IEffect.hh"
#include "Timer.hh"

class Spawn : public IEffect {
public:
    Spawn(irr::core::vector3df const & pos, float duration = 1.0f);
    Spawn(Spawn const & other);
    Spawn(Spawn && other);
    Spawn & operator = (Spawn const other);

    ~Spawn();

    bool isOver() const;

private:
    std::shared_ptr<irr::scene::IVolumeLightSceneNode>  _ln;
    Timer                                               _timer;
};


#endif //INDIESTUDIO_SPAWN_HH
