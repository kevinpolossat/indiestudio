//
// Created by kevin on 15/05/17.
//

#include "ResourcesManager.hh"

ResourcesManager::ResourcesManager(
        irr::video::E_DRIVER_TYPE driverType,
        irr::core::dimension2d<irr::u32> const &dim,
        uint32_t t):
        _device(irr::createDevice(driverType, dim, t)) {

}

ResourcesManager::~ResourcesManager() {
    _device->drop();
}

irr::scene::IAnimatedMesh *ResourcesManager::getAnimatedMesh(std::string const &name) const {
    auto val = _animatedMesh.find(name);
    if (val == _animatedMesh.end()) {
        throw std::range_error("Can't find: " + name);
    }
    return val->second;
}

void ResourcesManager::loadAnimatedMesh(
        std::string const &name,
        const std::string &path) {
    irr::scene::IAnimatedMesh* am = sceneManager()->getMesh((path + name).c_str());
    if (!am) {
        throw std::runtime_error("Can't load " + name);
    }
    _animatedMesh.insert(std::make_pair(name, am));
}

irr::video::IVideoDriver *ResourcesManager::videoDriver() const {
    return _device->getVideoDriver();
}

irr::scene::ISceneManager *ResourcesManager::sceneManager() const {
    return _device->getSceneManager();
}

irr::IrrlichtDevice *ResourcesManager::device() const {
    return _device;
}


