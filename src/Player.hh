#ifndef _PLAYER_HH__
#define _PLAYER_HH__

#include <irrlicht.h>
#include "EventHandler.hh"

class Player {
	enum AnimType {
		RUN,
		STAND,
		JUMP
	};

public:
	Player(irr::scene::ISceneManager * sceneManager,
	       irr::video::IVideoDriver * driver);
	~Player();

	void                                 addAnimator(irr::scene::ISceneNodeAnimator * animator);
	void                                 move(EventHandler const & receiver);

	irr::scene::IAnimatedMeshSceneNode * getMesh() const;
	irr::core::vector3df                 getPosition() const;

private:
	irr::scene::IAnimatedMeshSceneNode * _mesh;
	AnimType                             _anim;
};

#endif /*_PLAYER_HH__*/
