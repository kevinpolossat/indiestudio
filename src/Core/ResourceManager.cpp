//
// Created by kevin on 15/05/17.
//

#include "ResourceManager.hh"

ResourceManager::ResourceManager(
        irr::video::E_DRIVER_TYPE driverType,
        irr::core::dimension2d<irr::u32> const &dim,
        uint32_t t):
        _device(irr::createDevice(driverType, dim, t, false, false, false, &_handler), [](irr::IrrlichtDevice *dev) {dev->drop();}),
        _assimpLoader(_device->getSceneManager()) {
    _device->setWindowCaption(L"BomberBOOM");
}

ResourceManager::~ResourceManager() {
}

irr::scene::IAnimatedMesh *ResourceManager::getAnimatedMesh_impl(std::string const &name) const {
    auto val = _animatedMesh.find(name);
    if (val == _animatedMesh.end()) {
        throw std::range_error("Can't find: " + name);
    }
    return val->second;
}

void ResourceManager::loadAnimatedMesh_impl(
        std::string const &name,
        const std::string &path) {
    if (_animatedMesh.find(name) != _animatedMesh.end()) {
        return ;
    }
    irr::scene::IAnimatedMesh *am;
    if (_assimpLoader.isLoadable((path + name).c_str())) {
        am = _assimpLoader.getMesh((path + name).c_str());
    }
    else {
        am = _device->getSceneManager()->getMesh((path + name).c_str());
    }
    if (!am) {
        throw std::runtime_error("Can't load " + name);
    }
    _animatedMesh.insert(std::make_pair(name, am));
}

std::shared_ptr<irr::video::IVideoDriver> ResourceManager::videoDriver_impl() const {
    return {_device, _device->getVideoDriver()};
}

std::shared_ptr<irr::scene::ISceneManager> ResourceManager::sceneManager_impl() const {
    return {_device, _device->getSceneManager()};
}

std::shared_ptr<irr::IrrlichtDevice> ResourceManager::device_impl() const {
    return _device;
}

std::shared_ptr<irr::gui::IGUIEnvironment> ResourceManager::guiEnvironment_impl() const {
    return {_device, _device->getGUIEnvironment()};
}

EventHandler const &
ResourceManager::eventHandler_impl() {
    return _handler;
}

ResourceManager &ResourceManager::instance() {
    static ResourceManager rm;
    return rm;
}

std::shared_ptr<irr::IrrlichtDevice> ResourceManager::device() {
    return ResourceManager::instance().device_impl();
}

std::shared_ptr<irr::video::IVideoDriver> ResourceManager::videoDriver() {
    return ResourceManager::instance().videoDriver_impl();
}

std::shared_ptr<irr::scene::ISceneManager> ResourceManager::sceneManager() {
    return ResourceManager::instance().sceneManager_impl();
}

std::shared_ptr<irr::gui::IGUIEnvironment> ResourceManager::guiEnvironment() {
    return ResourceManager::instance().guiEnvironment_impl();
}

EventHandler const &ResourceManager::eventHandler() {
    return ResourceManager::instance().eventHandler_impl();
}

irr::scene::IAnimatedMesh *ResourceManager::getAnimatedMesh(std::string const &name) {
    return ResourceManager::instance().getAnimatedMesh_impl(name);
}

void ResourceManager::loadAnimatedMesh(std::string const &name, const std::string &path) {
    ResourceManager::instance().loadAnimatedMesh_impl(name, path);
}