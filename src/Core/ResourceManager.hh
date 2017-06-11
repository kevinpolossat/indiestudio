//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_RESOURCESMANAGER_HH
#define INDIESTUDIO_RESOURCESMANAGER_HH

#include <unordered_map>
#include <memory>
#include <irrlicht.h>
#include <SFML/Audio/SoundBuffer.hpp>
#include "EventHandler.hh"

class ResourceManager {

public:
    ~ResourceManager();


    static std::shared_ptr<irr::IrrlichtDevice>         device();
    static std::shared_ptr<irr::video::IVideoDriver>    videoDriver();
    static std::shared_ptr<irr::scene::ISceneManager>   sceneManager();
    static std::shared_ptr<irr::gui::IGUIEnvironment>   guiEnvironment();
    static EventHandler const &                         eventHandler();

    static irr::scene::IAnimatedMesh    *getAnimatedMesh(std::string const & name);
    static void                         loadAnimatedMesh(std::string const & name, std::string const &path = "./assets/");

    static void                         loadSound(std::string const & name, std::string const &path = "./assets/");
    static sf::SoundBuffer const &      getSound(std::string const & name);

private:
    EventHandler                                                    _handler;
    std::shared_ptr<irr::IrrlichtDevice>                            _device;
    std::unordered_map<std::string, irr::scene::IAnimatedMesh *>    _animatedMesh;
    std::unordered_map<std::string, sf::SoundBuffer>                _sounds;

private:
    explicit ResourceManager(irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL,
                             irr::core::dimension2d<irr::u32> const &dim = irr::core::dimension2d<irr::u32>(1920, 1080),
                             uint32_t t = 16);

    ResourceManager(ResourceManager const &)              = delete;
    ResourceManager(ResourceManager &&)                   = delete;

    ResourceManager & operator=(ResourceManager const &)  = delete;

    std::shared_ptr<irr::IrrlichtDevice>            device_impl()           const;
    std::shared_ptr<irr::video::IVideoDriver>       videoDriver_impl()      const;
    std::shared_ptr<irr::scene::ISceneManager>      sceneManager_impl()     const;
    std::shared_ptr<irr::gui::IGUIEnvironment>      guiEnvironment_impl()   const;
    EventHandler const &                            eventHandler_impl();

    irr::scene::IAnimatedMesh   *getAnimatedMesh_impl(std::string const & name) const;
    void                        loadAnimatedMesh_impl(std::string const & name, std::string const &path = "./assets/");

    void                        loadSound_impl(std::string const & name, std::string const &path = "./assets/");
    sf::SoundBuffer const &     getSound_impl(std::string const & name);

    static ResourceManager &    instance();
};

#endif //INDIESTUDIO_RESOURCESMANAGER_HH