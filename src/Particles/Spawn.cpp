//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>

#include "Spawn.hh"

Spawn::Spawn(irr::core::vector3df const & pos) {
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
