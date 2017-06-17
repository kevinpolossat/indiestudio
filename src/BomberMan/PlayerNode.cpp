//
// Created by vincent on 5/31/17.
//

#include <ResourceManager.hh>
#include "PlayerNode.hh"

PlayerNode::PlayerNode(irr::core::vector3df const &scale)
        : _node(nullptr),
          _offset(scale.X, 0, scale.Z),
          _anim(RUN),
          _scale(scale) {
    _offset *= 0.5f;
}

void PlayerNode::init(int id) {
    ResourceManager::loadAssimpMesh("player.fbx", ResourceManager::assets_rela + "player/");
    _node = ResourceManager::sceneManager()->addAnimatedMeshSceneNode(ResourceManager::getAnimatedMesh("player.fbx"));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    switch (id) {
        case 0:
            _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "player/texture/diffuse/Blue.png").c_str()));
            break;
        case 1:
            _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "player/texture/diffuse/Orange.png").c_str()));
            break;
        case 2:
            _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "player/texture/diffuse/Green.png").c_str()));
            break;
        case 3:
            _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "player/texture/diffuse/Purple.png").c_str()));
            break;

    }
    _node->setScale(irr::core::vector3df(0.2f, 0.2f, 0.2f));
    _node->setAnimationSpeed(15);
    _node->setFrameLoop(1, 51);
    _node->setLoopMode(true);
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

void PlayerNode::setOrientation(float const orientation) {
    _node->setRotation(irr::core::vector3df(0.f, orientation * (360.f / 4.f), 0.f));
}

void PlayerNode::setAnimation(const PlayerNode::AnimType & anim) {
    if (anim != _anim) {
        if (anim == RUN) {
            _node->setFrameLoop(60, 104);
            _node->setAnimationSpeed(20);
            _node->setLoopMode(true);
            _anim = RUN;
        } else {
            _node->setAnimationSpeed(15);
            _node->setFrameLoop(1, 51);
            _node->setLoopMode(true);
            _anim = STAND;
        }
    }
}
