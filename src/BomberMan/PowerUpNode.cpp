//
// Created by vincent on 6/6/17.
//

#include "PowerUpNode.hh"

PowerUpNode::PowerUpNode(irr::scene::ISceneNode * const node)
        : _node(node),
          _animationTime(-1) {
}

PowerUpNode::PowerUpNode(PowerUpNode const &other)
        : _node(other._node),
          _animationTime(other._animationTime){
}

PowerUpNode::PowerUpNode(PowerUpNode const &&other)
        : _node(other._node),
          _animationTime(other._animationTime) {
}

PowerUpNode::~PowerUpNode() {
}

PowerUpNode & PowerUpNode::operator=(PowerUpNode const & other) {
    if (this != &other) {
        _node = other._node;
    }
    return *this;
}

void PowerUpNode::update(std::vector<PowerUp> const & powerups, std::vector<std::shared_ptr<IPlayer>> const & players) {
    if (_animationTime == -1) {
        for (auto const & p : powerups) {
            if (_node->getID() == p.getId()) {
                return ;
            }
        }
        _animationTime = 60;
    } else if (_animationTime > 0) {
        irr::core::vector3df min(1000, 1000, 1000);
        for (std::shared_ptr<IPlayer> const & player : players) {
            if (player->getNode().getPosition().getDistanceFrom(_node->getPosition()) < player->getNode().getPosition().getDistanceFrom(min)) {
                min = player->getNode().getPosition();
            }
        }
        --_animationTime;
        _node->setScale(_node->getScale() * 0.95f);
        _node->removeAnimators();
        _node->addAnimator(ResourceManager::sceneManager()->createFlyCircleAnimator(min, 1.0f, 0.02f, irr::core::vector3df(0.f, 1.f, 0.f), static_cast<float>(_animationTime) / 20.f));
    } else {
        _node->remove();
        _node = nullptr;
    }
}

irr::s32 PowerUpNode::getId() const {
    return _node->getID();
}

bool PowerUpNode::isToBeRemoved() const {
    return _node == nullptr;
}