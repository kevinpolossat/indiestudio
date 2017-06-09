//
// Created by kevin on 09/06/17.
//

#include "ResourceManager.hh"
#include "UniformExplosion.hh"

UniformExplosion::UniformExplosion(irr::core::vector3df const &pos, float duration): _timer(duration) {
    irr::core::array<irr::video::ITexture*> textures;
    for (irr::s32 g = 1; g < 8; ++g)
    {
        irr::core::stringc tmp("./assets/light_spawn/portal");
        tmp += g;
        tmp += ".bmp";
        irr::video::ITexture* t = ResourceManager::videoDriver()->getTexture(tmp);
        textures.push_back(t);
    }
    irr::scene::ISceneNodeAnimator *anim = ResourceManager::sceneManager()->createTextureAnimator(textures, 100);
    _bb = std::shared_ptr<irr::scene::IBillboardSceneNode>(ResourceManager::sceneManager()->addBillboardSceneNode(
            0, irr::core::dimension2d<irr::f32>(7.5f, 7.5f), pos
    ), [](irr::scene::IBillboardSceneNode *bb) {
       bb->remove();
    });
    _bb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _bb->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("./assets/light_spawn/portal1.bmp"));
    _bb->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    _bb->addAnimator(anim);

    anim->drop();
}

UniformExplosion::~UniformExplosion() {

}

UniformExplosion::UniformExplosion(UniformExplosion const &other): _timer(other._timer) {

}

UniformExplosion::UniformExplosion(UniformExplosion &&other): _timer(other._timer) {

}

UniformExplosion &UniformExplosion::operator=(UniformExplosion const &other) {
    _timer = other._timer;
    return *this;
}

bool UniformExplosion::isOver() const {
    return _timer.isOver();
}

void UniformExplosion::update() {

}
