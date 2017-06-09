//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_UNIFORMEXPLOSION_HH
#define INDIESTUDIO_UNIFORMEXPLOSION_HH

#include <memory>

#include "irrlicht.h"
#include "IEffect.hh"
#include "Timer.hh"

class UniformExplosion: public IEffect {
public:
    UniformExplosion(irr::core::vector3df const & pos, float duration = 1.0f);
    ~UniformExplosion();

    UniformExplosion(UniformExplosion const & other);
    UniformExplosion(UniformExplosion && other);
    UniformExplosion & operator = (UniformExplosion const & other);

    bool isOver() const;
    void update();
private:
    std::shared_ptr<irr::scene::IBillboardSceneNode>    _bb;
    Timer                                               _timer;
};


#endif //INDIESTUDIO_UNIFORMEXPLOSION_HH
