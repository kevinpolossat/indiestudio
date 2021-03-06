//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>
#include "Explosion.hh"

Explosion::Explosion(irr::core::vector3df const & pos, uint32_t duration, float scale): _timer(duration), _scale(scale) {
    _ps = std::shared_ptr<irr::scene::IParticleSystemSceneNode>(
            ResourceManager::sceneManager()->addParticleSystemSceneNode(false),
            [](irr::scene::IParticleSystemSceneNode *_ips) {
                _ips->remove();
            }
    );
    irr::scene::IParticleEmitter* em = _ps->createSphereEmitter(irr::core::vector3df(0.0f, 0.0f, 0.0f),
                                                          1.0f,
                                                          irr::core::vector3df(0.0f, 0.2f, 0.0f),
                                                          300, 400,
                                                          irr::video::SColor(255, 0, 230, 118),
                                                          irr::video::SColor(255, 0, 200, 83),
                                                          15, 25, 360,
                                                          irr::core::dimension2df(0.2f, 0.2f),
                                                          irr::core::dimension2df(3.f, 3.f));
    _ps->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector *paf = _ps->createFadeOutParticleAffector(irr::video::SColor(0, 255, 255, 255), 250);
    _ps->addAffector(paf);
    paf->drop();
    irr::scene::IParticleAffector *saf =  _ps->createScaleParticleAffector(irr::core::dimension2df(0.f, 0.f));
    _ps->addAffector(saf);
    saf->drop();
    _ps->setPosition(pos);
    _ps->setScale(irr::core::vector3df(1, 1, 1));
    _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _ps->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "light_spawn/portal1.bmp").c_str()));
    _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Explosion::~Explosion() {
}

Explosion::Explosion(Explosion const &other): _ps(other._ps), _timer(other._timer), _scale(other._scale) {
}

Explosion::Explosion(Explosion &&other): _ps(other._ps), _timer(other._timer), _scale(other._scale) {
}

Explosion &Explosion::operator=(Explosion const &other) {
    _ps         = other._ps;
    _timer      = other._timer;
    _scale      = other._scale;
    return *this;
}

bool Explosion::isOver() const {
    return _timer.isOver();
}

void Explosion::update() {
    _timer.update();
}
