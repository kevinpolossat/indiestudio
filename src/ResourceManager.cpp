//
// Created by kevin on 15/05/17.
//

#include "ResourceManager.hh"

ResourceManager rm;

ResourceManager::ResourceManager(
        irr::video::E_DRIVER_TYPE driverType,
        irr::core::dimension2d<irr::u32> const &dim,
        uint32_t t):
        _device(irr::createDevice(driverType, dim, t)) {

}

ResourceManager::~ResourceManager() {
    _device->drop();
}

irr::scene::IAnimatedMesh *ResourceManager::getAnimatedMesh(std::string const &name) const {
    auto val = _animatedMesh.find(name);
    if (val == _animatedMesh.end()) {
        throw std::range_error("Can't find: " + name);
    }
    return val->second;
}

void ResourceManager::loadAnimatedMesh(
        std::string const &name,
        const std::string &path) {
    if (_animatedMesh.find(name) != _animatedMesh.end()) {
        return ;
    }
    irr::scene::IAnimatedMesh* am = sceneManager()->getMesh((path + name).c_str());
    if (!am) {
        throw std::runtime_error("Can't load " + name);
    }
    _animatedMesh.insert(std::make_pair(name, am));
}

irr::video::IVideoDriver *ResourceManager::videoDriver() const {
    return _device->getVideoDriver();
}

irr::scene::ISceneManager *ResourceManager::sceneManager() const {
    return _device->getSceneManager();
}

irr::IrrlichtDevice *ResourceManager::device() const {
    return _device;
}

irr::gui::IGUIEnvironment *ResourceManager::guiEnvironment() const {
    return _device->getGUIEnvironment();
}