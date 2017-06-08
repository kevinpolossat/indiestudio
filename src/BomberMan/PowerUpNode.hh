//
// Created by vincent on 6/6/17.
//

#ifndef INDIESTUDIO_POWERUPNODE_HH
#define INDIESTUDIO_POWERUPNODE_HH


#include <ISceneNode.h>
#include "PowerUp.hh"
#include "IPlayer.hh"

class PowerUpNode {
public:
    PowerUpNode(irr::scene::ISceneNode * const node);
    PowerUpNode(PowerUpNode const & other);
    PowerUpNode(PowerUpNode const && other);
    ~PowerUpNode();

    void     update(std::vector<PowerUp> const & powerups, std::vector<std::shared_ptr<IPlayer>> const & players);
    bool     isToBeRemoved() const;
    irr::s32 getId() const;

    PowerUpNode & operator=(PowerUpNode const & other);

private:
    irr::scene::ISceneNode * _node;
    irr::s32                 _animationTime;
};


#endif //INDIESTUDIO_POWERUPNODE_HH
