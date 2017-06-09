//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>

#include "Spawn.hh"

Spawn::Spawn(irr::core::vector3df const & pos, float duration): _timer(duration) {
    _ln = std::shared_ptr<irr::scene::IVolumeLightSceneNode>(ResourceManager::sceneManager()->addVolumeLightSceneNode(
            0, -1, 32, 32, irr::video::SColor(0, 255, 255, 255), irr::video::SColor(0, 0, 0, 0)),
    [](irr::scene::IVolumeLightSceneNode * ln){ ln->remove(); });

    if (_ln)
    {
        _ln->setScale(irr::core::vector3df(1.0f, 1.0f, 1.0f));
        _ln->setPosition(pos);

        irr::core::array<irr::video::ITexture*> textures;
        for (irr::s32 g = 7; g > 0; --g)
        {
            irr::core::stringc tmp;
            tmp = "./assets/light_spawn/portal";
            tmp += g;
            tmp += ".bmp";
            irr::video::ITexture* t = ResourceManager::videoDriver()->getTexture(tmp.c_str());
            textures.push_back(t);
        }
        irr::scene::ISceneNodeAnimator* glow = ResourceManager::sceneManager()->createTextureAnimator(textures, 150);
        _ln->addAnimator(glow);
        glow->drop();
    }
}

Spawn::~Spawn() {

}

Spawn::Spawn(Spawn const &other): _ln(other._ln), _timer(other._timer) {
}

Spawn::Spawn(Spawn &&other): _ln(other._ln), _timer(other._timer) {
}

Spawn &Spawn::operator=(Spawn const other) {
    _ln     = other._ln;
    _timer  = other._timer;
    return *this;
}

bool Spawn::isOver() const {
    return _timer.isOver();
}
