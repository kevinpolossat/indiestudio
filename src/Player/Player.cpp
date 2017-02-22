#include "Player.hh"

Player::Player(irr::scene::ISceneManager * sceneManager,
               irr::video::IVideoDriver * driver)
	: _mesh(sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("media/sydney.md2"))),
	_anim(STAND)
{
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_mesh->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
	_mesh->setMD2Animation(irr::scene::EMAT_STAND);
	_mesh->setPosition(irr::core::vector3df(100, 0, 100));
}

Player::~Player() {

}

void Player::move(EventHandler const & receiver) {
	irr::core::vector3df vs = _mesh->getPosition();
	if (receiver.isKeyDown(irr::KEY_KEY_Z)) {
		vs.Z += 2.0f;
	}
	if (receiver.isKeyDown(irr::KEY_KEY_S)) {
		vs.Z -= 2.0f;
	}
	if (receiver.isKeyDown(irr::KEY_KEY_Q)) {
		vs.X -= 2.0f;
	}
	if (receiver.isKeyDown(irr::KEY_KEY_D)) {
		vs.X += 2.0f;
	}
	if (receiver.isKeyDown(irr::KEY_SPACE) && _anim != JUMP) {
		vs.Y += 10.0f;
		_mesh->setMD2Animation(irr::scene::EMAT_JUMP);
    _mesh->setLoopMode(false);
		_anim = JUMP;
  } else if (_anim == JUMP) {
    irr::core::list<irr::scene::ISceneNodeAnimator*>::ConstIterator itAnim = _mesh->getAnimators().begin();
    irr::scene::ISceneNodeAnimatorCollisionResponse* animator = static_cast<irr::scene::ISceneNodeAnimatorCollisionResponse*>(*itAnim);
    if (animator && animator->collisionOccurred()) {
      _anim = STAND;
      _mesh->setMD2Animation(irr::scene::EMAT_STAND);
      _mesh->setLoopMode(true);
    } else {
      vs.Y += 10.0f;
    }
	} else if (vs != _mesh->getPosition()) {
		if (_anim != JUMP && _anim != RUN) {
			_mesh->setMD2Animation(irr::scene::EMAT_RUN);
      _mesh->setLoopMode(true);
			_anim = RUN;
		}
	} else {
		if (_anim != STAND) {
			_mesh->setMD2Animation(irr::scene::EMAT_STAND);
      _mesh->setLoopMode(true);
			_anim = STAND;
		}
	}
	_mesh->setPosition(vs);
	irr::core::vector2d<irr::s32> cursor(receiver.getMousePos().X - 320, receiver.getMousePos().Y - 240);
	_mesh->setRotation(irr::core::vector3df(0, cursor.getAngleTrig(), 0));
}

void Player::addAnimator(irr::scene::ISceneNodeAnimator * animator) {
	_mesh->addAnimator(animator);
}

irr::scene::IAnimatedMeshSceneNode * Player::getMesh() const {
	return _mesh;
}

irr::core::vector3df Player::getPosition() const {
	return _mesh->getPosition();
}
