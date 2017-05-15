//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_RESOURCESMANAGER_HH
#define INDIESTUDIO_RESOURCESMANAGER_HH

#include <unordered_map>
#include <memory>
#include <irrlicht.h>

class ResourceManager {

public:
    explicit ResourceManager(irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL,
                     irr::core::dimension2d<irr::u32> const &dim = irr::core::dimension2d<irr::u32>(640,480),
                     uint32_t t = 32);
    ~ResourceManager();

    ResourceManager(ResourceManager const &)              = delete;
    ResourceManager(ResourceManager &&)                   = delete;

    ResourceManager & operator=(ResourceManager const &)  = delete;

    irr::IrrlichtDevice         *device()           const;
    irr::video::IVideoDriver    *videoDriver()      const;
    irr::scene::ISceneManager   *sceneManager()     const;
    irr::gui::IGUIEnvironment   *guiEnvironment()   const;

    irr::scene::IAnimatedMesh   *getAnimatedMesh(std::string const & name) const;
    void                        loadAnimatedMesh(std::string const & name, std::string const &path = "./assets");
private:
    irr::IrrlichtDevice                                             *_device;
    std::unordered_map<std::string, irr::scene::IAnimatedMesh *>    _animatedMesh;
};

extern ResourceManager rm;

#endif //INDIESTUDIO_RESOURCESMANAGER_HH