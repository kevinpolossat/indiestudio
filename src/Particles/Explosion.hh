//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_EXPLOSION_HH
#define INDIESTUDIO_EXPLOSION_HH

#include <irrlicht.h>
#include <memory>

class Explosion {
public:
    explicit Explosion(irr::core::vector3df const & pos);

    Explosion(Explosion const & other);
    Explosion(Explosion && other);
    Explosion & operator = (Explosion const & other);

    ~Explosion();
private:
    std::shared_ptr<irr::scene::IParticleSystemSceneNode> _ps;
};


#endif //INDIESTUDIO_EXPLOSION_HH
