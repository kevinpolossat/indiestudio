//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>
#include "Explosion.hh"

Explosion::Explosion() {
    irr::scene::IParticleSystemSceneNode* ps =
            ResourceManager::sceneManager()->addParticleSystemSceneNode(false);

//    scene::IParticleEmitter* em = ps->createRingEmitter(
//    scene::IParticleEmitter* em = ps->createRingEmitter(
    irr::scene::IParticleEmitter* em = ps->createSphereEmitter(irr::core::vector3df(0.0f, 0.0f, 0.0f),
                                                          1.0f,
                                                          irr::core::vector3df(0.0f, 0.2f, 0.0f),
                                                          3000, 4000,
                                                          irr::video::SColor(255, 0, 230, 118),
                                                          irr::video::SColor(255, 0, 200, 83),
                                                          150, 250, 360,
                                                          irr::core::dimension2df(5.f, 5.f),
                                                          irr::core::dimension2df(6.f, 6.f));


    ps->setEmitter(em); // this grabs the emitter
    em->drop(); // so we can drop it here without deleting it

    irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector(irr::video::SColor(0, 255, 255, 255), 250);

    ps->addAffector(paf); // same goes for the affector
    paf->drop();

    irr::scene::IParticleAffector * scaleAff =  ps->createScaleParticleAffector(irr::core::dimension2df(0.f, 0.f));
    ps->addAffector(scaleAff);
    scaleAff->drop();

    ps->setPosition(irr::core::vector3df(-70,75,40));
    ps->setScale(irr::core::vector3df(2,2,2));
    ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("./dependencies/irrlicht/Source/Irrlicht/media/particlegreen.jpg"));
    ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Explosion::~Explosion() {

}
