#include "Player.hh"

Player::Player(uint8_t const id,
               std::array<irr::EKEY_CODE, 5> keyMap)
        : _node(NULL),
          _anim(STAND),
          _id(id),
          _keyMap(keyMap),
          _ctrllrId(-1)
{
    ResourceManager::loadAnimatedMesh("sydney.md2");
    _node = ResourceManager::sceneManager()->addAnimatedMeshSceneNode(ResourceManager::getAnimatedMesh("sydney.md2"));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/sydney.bmp"));
    _node->setMD2Animation(irr::scene::EMAT_STAND);
    _node->setPosition(irr::core::vector3df(100, 500, -100));
}

Player::~Player() {

}

void Player::move(EventHandler const & receiver, Referee & referee) {
    irr::core::vector3df vs = _node->getPosition();
    if (!this->_isUsingCtrllr) {
        if (receiver.isKeyDown(this->_keyMap[0])) {
            referee.doAction(this->_id, Action::UP, 1);
//            vs.Z += 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[1])) {
            referee.doAction(this->_id, Action::RIGHT, 1);
//            vs.X += 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[2])) {
            referee.doAction(this->_id, Action::DOWN, 1);
//            vs.Z -= 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[3])) {
            referee.doAction(this->_id, Action::LEFT, 1);
//            vs.X -= 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[4]) && _anim != JUMP) {
            //referee->placeBomb(this->_id, BOMB);
            vs.Y += 10.0f;
            _node->setMD2Animation(irr::scene::EMAT_JUMP);
            _node->setLoopMode(false);
            _anim = JUMP;
        } else if (_anim == JUMP) {
            irr::core::list<irr::scene::ISceneNodeAnimator *>::ConstIterator itAnim = _node->getAnimators().begin();
            irr::scene::ISceneNodeAnimatorCollisionResponse *animator = static_cast<irr::scene::ISceneNodeAnimatorCollisionResponse *>(*itAnim);
            if (animator && animator->collisionOccurred()) {
                _anim = STAND;
                _node->setMD2Animation(irr::scene::EMAT_STAND);
                _node->setLoopMode(true);
            } else {
                vs.Y += 10.0f;
            }
        } else if (vs != _node->getPosition()) {
            if (_anim != JUMP && _anim != RUN) {
                _node->setMD2Animation(irr::scene::EMAT_RUN);
                _node->setLoopMode(true);
                _anim = RUN;
            }
        } else {
            if (_anim != STAND) {
                _node->setMD2Animation(irr::scene::EMAT_STAND);
                _node->setLoopMode(true);
                _anim = STAND;
            }
        }
        _node->setPosition(vs);
        irr::core::vector2d<irr::s32> cursor(receiver.getMousePos().X - 320, receiver.getMousePos().Y - 240);
        _node->setRotation(irr::core::vector3df(0, static_cast<irr::f32>(cursor.getAngleTrig()), 0));
    } else if (this->_ctrllrId > -1) {
        irr::f32    vertMove = 0.f;
        irr::f32    horiMove = 0.f;

        const irr::SEvent::SJoystickEvent   &joystick = receiver.getJoystick(static_cast<irr::u8>(this->_ctrllrId));

        const irr::f32                      deadZone = 0.05f;

        horiMove =
                static_cast<irr::f32>(joystick.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f);
        if(fabs(static_cast<float>(horiMove)) < deadZone) {
            horiMove = 0.f;
        }

        vertMove = static_cast<irr::f32>(joystick.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f);
        if(fabs(static_cast<float>(vertMove)) < deadZone) {
            vertMove = 0.f;
        }

        (void)horiMove;
        (void)vertMove;
        //referee->move(this->_id, horiMove * 2, vertMove * 2)
    }
}

void Player::addAnimator(irr::scene::ISceneNodeAnimator * animator) {
    _node->addAnimator(animator);
}

irr::scene::IAnimatedMeshSceneNode * Player::getMesh() const {
    return _node;
}

irr::core::vector3df const &
Player::getPosition() const {
    return _node->getPosition();
}

void
Player::setCtrllrId(int32_t const id) {
    this->_ctrllrId = id;
}

void
Player::setUsingCtrllr(const bool state) {
    this->_isUsingCtrllr = state;
}

int32_t const
Player::getCtrllrId() const {
    return this->_ctrllrId;
}

bool const
Player::getIsUsingCtrllr() const {
    return this->_isUsingCtrllr;
}

void Player::setPosition(irr::core::vector3df const & pos) {
    _node->setPosition(pos);
}
