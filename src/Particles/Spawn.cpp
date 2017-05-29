//
// Created by kevin on 26/05/17.
//

#include <irrlicht.h>
#include <ResourceManager.hh>

#include "Spawn.hh"

Spawn::Spawn() {
    irr::scene::IVolumeLightSceneNode * n = ResourceManager::sceneManager()->addVolumeLightSceneNode(0, -1,
                                                                     32,                              // Subdivisions on U axis
                                                                     32,                              // Subdivisions on V axis
                                                                     irr::video::SColor(0, 255, 255, 255), // foot color
                                                                     irr::video::SColor(0, 0, 0, 0));      // tail color

    if (n)
    {
        n->setScale(irr::core::vector3df(56.0f, 56.0f, 56.0f));
        n->setPosition(irr::core::vector3df(-120,50,40));

        // load textures for animation
        irr::core::array<irr::video::ITexture*> textures;
        for (irr::s32 g=7; g > 0; --g)
        {
            irr::core::stringc tmp;
            tmp = "./dependencies/irrlicht/Source/Irrlicht/media/portal";
            tmp += g;
            tmp += ".bmp";
            irr::video::ITexture* t = ResourceManager::videoDriver()->getTexture( tmp.c_str() );
            textures.push_back(t);
        }

        // create texture animator
        irr::scene::ISceneNodeAnimator* glow = ResourceManager::sceneManager()->createTextureAnimator(textures, 150);

        // add the animator
        n->addAnimator(glow);

        // drop the animator because it was created with a create() function
        glow->drop();
    }

}

Spawn::~Spawn() {

}
