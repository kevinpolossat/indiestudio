//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_EXPLOSION_HH
#define INDIESTUDIO_EXPLOSION_HH

#include <irrlicht.h>
#include <memory>
#include <chrono>

#include "Timer.hh"
#include "IEffect.hh"

class Explosion : public IEffect {
public:
    explicit Explosion(irr::core::vector3df const & pos, uint32_t duration = 1, float scale = 1.0f);

    Explosion(Explosion const & other);
    Explosion(Explosion && other);
    Explosion & operator = (Explosion const & other);

    ~Explosion();

    bool    isOver() const;
    void    update();
private:
    std::shared_ptr<irr::scene::IParticleSystemSceneNode>   _ps;
    Timer                                                   _timer;
    float                                                   _scale;
};


#endif //INDIESTUDIO_EXPLOSION_HH
