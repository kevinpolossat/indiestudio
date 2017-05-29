//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>
#include "Explosion.hh"

Explosion::Explosion(irr::core::vector3df const & pos) {
    _ps = ResourceManager::sceneManager()->addParticleSystemSceneNode(false);
    irr::scene::IParticleEmitter* em = _ps->createSphereEmitter(irr::core::vector3df(0.0f, 0.0f, 0.0f),
                                                          1.0f,
                                                          irr::core::vector3df(0.0f, 0.2f, 0.0f),
                                                          3000, 4000,
                                                          irr::video::SColor(255, 0, 230, 118),
                                                          irr::video::SColor(255, 0, 200, 83),
                                                          150, 250, 360,
                                                          irr::core::dimension2df(5.f, 5.f),
                                                          irr::core::dimension2df(6.f, 6.f));


    _ps->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector* paf = _ps->createFadeOutParticleAffector(irr::video::SColor(0, 255, 255, 255), 250);
    _ps->addAffector(paf);
    paf->drop();
    irr::scene::IParticleAffector * saf =  _ps->createScaleParticleAffector(irr::core::dimension2df(0.f, 0.f));
    _ps->addAffector(saf);
    saf->drop();
    _ps->setPosition(pos);
    _ps->setScale(irr::core::vector3df(2,2,2));
    _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _ps->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("./dependencies/irrlicht/Source/Irrlicht/media/particlegreen.jpg"));
    _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Explosion::~Explosion() {
    _ps->remove();
}
