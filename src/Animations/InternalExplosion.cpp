//
// Created by kevin on 09/06/17.
//

#include "ResourceManager.hh"
#include "InternalExplosion.hh"

InternalExplosion::InternalExplosion(irr::core::vector3df const &pos,
                                   uint32_t duration,
                                   float initialSize): _timer(duration), _initialSize(initialSize) {
    irr::core::array<irr::video::ITexture*> textures;
    for (irr::s32 g = 1; g < 8; ++g)
    {
        irr::core::stringc tmp((ResourceManager::assets_rela + "light_spawn/portal").c_str());
        tmp += g;
        tmp += ".bmp";
        irr::video::ITexture* t = ResourceManager::videoDriver()->getTexture(tmp);
        textures.push_back(t);
    }
    irr::scene::ISceneNodeAnimator *anim = ResourceManager::sceneManager()->createTextureAnimator(textures, 100);
    _bb = std::shared_ptr<irr::scene::IBillboardSceneNode>(ResourceManager::sceneManager()->addBillboardSceneNode(
            0, irr::core::dimension2d<irr::f32>(_initialSize, _initialSize), pos
    ), [](irr::scene::IBillboardSceneNode *bb) {
       bb->remove();
    });
    _bb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _bb->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "light_spawn/portal1.bmp").c_str()));
    _bb->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    _bb->addAnimator(anim);

    anim->drop();
}

InternalExplosion::~InternalExplosion() {

}

InternalExplosion::InternalExplosion(InternalExplosion const &other): _timer(other._timer), _initialSize(other._initialSize) {

}

InternalExplosion::InternalExplosion(InternalExplosion &&other): _timer(other._timer), _initialSize(other._initialSize) {

}

InternalExplosion &InternalExplosion::operator=(InternalExplosion const &other) {
    _timer          = other._timer;
    _initialSize    = other._initialSize;
    return *this;
}

bool InternalExplosion::isOver() const {
    return _timer.isOver();
}

void InternalExplosion::update() {
    _timer.update();
    auto ratio      = std::max(1.0f - static_cast<float>(_timer.elapse()) / static_cast<float>(_timer.duration()), 0.1f);
    auto newWidth   = _initialSize * ratio;
    auto newHeight  = _initialSize * ratio;
    _bb->setSize(irr::core::dimension2d<irr::f32>(newWidth, newHeight));
}

