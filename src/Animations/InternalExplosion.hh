//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_UNIFORMEXPLOSION_HH
#define INDIESTUDIO_UNIFORMEXPLOSION_HH

#include <memory>

#include "irrlicht.h"
#include "IEffect.hh"
#include "Timer.hh"

class InternalExplosion: public IEffect {
public:
    InternalExplosion(irr::core::vector3df const & pos, uint32_t duration = 1, float initialSize = 8.0f);
    ~InternalExplosion();

    InternalExplosion(InternalExplosion const & other);
    InternalExplosion(InternalExplosion && other);
    InternalExplosion & operator = (InternalExplosion const & other);

    bool isOver() const;
    void update();
private:
    std::shared_ptr<irr::scene::IBillboardSceneNode>    _bb;
    Timer                                               _timer;
    float                                               _initialSize;
};


#endif //INDIESTUDIO_UNIFORMEXPLOSION_HH
