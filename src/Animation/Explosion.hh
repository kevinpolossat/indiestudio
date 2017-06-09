//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_EXPLOSION_HH
#define INDIESTUDIO_EXPLOSION_HH

#include <irrlicht.h>
#include <memory>
#include <chrono>

class Explosion {
public:
    explicit Explosion(irr::core::vector3df const & pos, float duration = 1.0f);

    Explosion(Explosion const & other);
    Explosion(Explosion && other);
    Explosion & operator = (Explosion const & other);

    ~Explosion();

    bool    isOver() const;
private:
    std::shared_ptr<irr::scene::IParticleSystemSceneNode>   _ps;
    float                                                   _duration;
    std::chrono::steady_clock::time_point                   _tStart;
};


#endif //INDIESTUDIO_EXPLOSION_HH