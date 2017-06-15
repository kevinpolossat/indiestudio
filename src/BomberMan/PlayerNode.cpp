//
// Created by vincent on 5/31/17.
//

#include <ResourceManager.hh>
#include "PlayerNode.hh"

PlayerNode::PlayerNode(irr::core::vector3df const &scale)
        : _node(nullptr),
          _offset(scale.X, 0, scale.Z),
          _anim(STAND),
          _scale(scale) {
    _offset *= 0.5f;
}

void PlayerNode::init() {
    ResourceManager::loadAssimpMesh("player.fbx", "assets/player/");
    _node = ResourceManager::sceneManager()->addAnimatedMeshSceneNode(ResourceManager::getAnimatedMesh("player.fbx"));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/player/texture/diffuse/Blue.png"));
//    _node->setMD2Animation(irr::scene::EMAT_STAND);
    _node->setScale(irr::core::vector3df(0.2f, 0.2f, 0.2f));
}

PlayerNode::PlayerNode(PlayerNode const &other)
        : _node(nullptr),
          _offset(other._offset),
          _anim(other._anim),
          _scale(other._scale) {
}

PlayerNode::~PlayerNode() {
    if (_node) {
        _node->remove();
    }
}

irr::scene::IAnimatedMeshSceneNode * PlayerNode::getMesh() const {
    return _node;
}

irr::core::vector3df PlayerNode::getPosition() const {
    return _node->getPosition();
}

void PlayerNode::setPosition(irr::core::vector3df const & pos) {

    _node->setPosition(pos - _offset);
}


