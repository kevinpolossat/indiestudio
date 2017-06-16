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
#include "IrrAssimp.h"

//#define BOMBERMAN_RELEASE

class ResourceManager {

public:
    ~ResourceManager();

    static std::string const assets_rela;


    static std::shared_ptr<irr::IrrlichtDevice>         device();
    static std::shared_ptr<irr::video::IVideoDriver>    videoDriver();
    static std::shared_ptr<irr::scene::ISceneManager>   sceneManager();
    static std::shared_ptr<irr::gui::IGUIEnvironment>   guiEnvironment();
    static EventHandler &                               eventHandler();

    static irr::scene::IAnimatedMesh    *getAnimatedMesh(std::string const & name);
    static void                         loadAnimatedMesh(std::string const & name, std::string const &path = assets_rela);
    static void                         loadAssimpMesh(std::string const & name, std::string const &path = assets_rela);
    static std::array<int, 2> &         getControllers();
    #ifdef SOUND
    static void                         loadSound(std::string const & name, std::string const &path = assets_rela/*"./assets/"*/);
    static sf::SoundBuffer const &      getSound(std::string const & name);
#endif
private:
    EventHandler                                                    _handler;
    std::shared_ptr<irr::IrrlichtDevice>                            _device;
    std::unordered_map<std::string, irr::scene::IAnimatedMesh *>    _animatedMesh;
    std::array<int, 2>                                              _controllers;
  #ifdef SOUND
    std::unordered_map<std::string, sf::SoundBuffer>                _sounds;
  #endif
    IrrAssimp                                                       _assimpImporter;
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
    EventHandler &                                  eventHandler_impl();

    irr::scene::IAnimatedMesh   *getAnimatedMesh_impl(std::string const & name) const;
    void                        loadAnimatedMesh_impl(std::string const & name, std::string const &path = assets_rela);
    void                        loadAssimpMesh_impl(std::string const & name, std::string const &path = assets_rela);
    std::array<int, 2> &        getControllers_impl();

    #ifdef SOUND
    void                        loadSound_impl(std::string const & name, std::string const &path = assets_rela/*"./assets/"*/);
    sf::SoundBuffer const &     getSound_impl(std::string const & name);
#endif
    static ResourceManager &    instance();
};

#endif //INDIESTUDIO_RESOURCESMANAGER_HH
