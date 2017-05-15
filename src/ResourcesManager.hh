//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_RESOURCESMANAGER_HH
#define INDIESTUDIO_RESOURCESMANAGER_HH

#include <unordered_map>
#include <memory>
#include <irrlicht.h>

class ResourcesManager {

public:
    ResourcesManager(irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL,
                     irr::core::dimension2d<irr::u32> const &dim = irr::core::dimension2d<irr::u32>(640,480),
                     uint32_t t = 32);
    ~ResourcesManager();

    ResourcesManager(ResourcesManager const &)              = delete;
    ResourcesManager(ResourcesManager &&)                   = delete;

    ResourcesManager & operator=(ResourcesManager const &)  = delete;

    irr::IrrlichtDevice         *device()       const;
    irr::video::IVideoDriver    *videoDriver()  const;
    irr::scene::ISceneManager   *sceneManager() const;

    irr::scene::IAnimatedMesh   *getAnimatedMesh(std::string const & name) const;
    void                        loadAnimatedMesh(std::string const & name, std::string const &path = "./assets");
private:
    irr::IrrlichtDevice                                             *_device;
    std::unordered_map<std::string, irr::scene::IAnimatedMesh *>    _animatedMesh;
};


#endif //INDIESTUDIO_RESOURCESMANAGER_HH