//
// Created by vincent on 5/31/17.
//

#include <ResourceManager.hh>
#include "PlayerNode.hh"

PlayerNode::PlayerNode(irr::core::vector3df const &scale)
        : _node(nullptr),
          _offset(0, 0, scale.Z),
          _anim(STAND) {
    ResourceManager::loadAnimatedMesh("sydney.md2");
    _node = ResourceManager::sceneManager()->addAnimatedMeshSceneNode(ResourceManager::getAnimatedMesh("sydney.md2"));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/sydney.bmp"));
    _node->setMD2Animation(irr::scene::EMAT_STAND);
    _node->setPosition(irr::core::vector3df(0, 0, 0));
    float playerScale = (2 * scale.Y) / _node->getBoundingBox().getExtent().Y;
    _node->setScale(irr::core::vector3df(playerScale, playerScale, playerScale));
}

PlayerNode::PlayerNode(PlayerNode const &other)
        : _node(other._node),
          _offset(other._offset),
          _anim(other._anim) {
}

PlayerNode::~PlayerNode() {

}

irr::scene::IAnimatedMeshSceneNode * PlayerNode::getMesh() const {
    return _node;
}

irr::core::vector3df PlayerNode::getPosition() const {
    return _node->getPosition() - _offset;
}

void PlayerNode::setPosition(irr::core::vector3df const & pos) {
    _node->setPosition(pos - _offset);
}

