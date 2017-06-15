//
// Created by vincent on 5/31/17.
//

#ifndef INDIESTUDIO_PLAYERNODE_HH
#define INDIESTUDIO_PLAYERNODE_HH


#include <vector3d.h>
#include <IAnimatedMeshSceneNode.h>

class PlayerNode {
public:
    enum AnimType {
        RUN,
        STAND
    };

    PlayerNode(irr::core::vector3df const & scale);
    PlayerNode(PlayerNode const & other);
    PlayerNode(PlayerNode const && other) = delete;
    ~PlayerNode();

    void                                 init();
    irr::scene::IAnimatedMeshSceneNode * getMesh() const;
    irr::core::vector3df                 getPosition() const;
    void                                 setPosition(irr::core::vector3df const & pos);
    void                                 setAnimation(AnimType const & anim);

private:
    irr::scene::IAnimatedMeshSceneNode          *_node;
    irr::core::vector3df                         _offset;
    AnimType                                     _anim;
    irr::core::vector3df                         _scale;
};


#endif //INDIESTUDIO_PLAYERNODE_HH
