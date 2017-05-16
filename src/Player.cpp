#include "Player.hh"

Player::Player(ResourceManager & rm, uint8_t const id,
               std::array<irr::EKEY_CODE, 5> keyMap)
        : _mesh(NULL),
          _anim(STAND),
          _id(id),
          _keyMap(keyMap),
          _ctrllrId(-1)
{
    rm.loadAnimatedMesh("sydney.md2");
    _mesh = rm.sceneManager()->addAnimatedMeshSceneNode(rm.getAnimatedMesh("sydney.md2"));
    _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, rm.videoDriver()->getTexture("assets/sydney.bmp"));
    _mesh->setMD2Animation(irr::scene::EMAT_STAND);
    _mesh->setPosition(irr::core::vector3df(100, 500, -100));
}

Player::~Player() {

}

void Player::move(EventHandler const & receiver) {
    irr::core::vector3df vs = _mesh->getPosition();
    if (!this->_isUsingCtrllr) {
        if (receiver.isKeyDown(this->_keyMap[0])) {
            //referee->move(this->_id, MOVE_UP);
            vs.Z += 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[1])) {
            //referee->move(this->_id, MOVE_RIGHT);
            vs.X += 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[2])) {
            //referee->move(this->_id, MOVE_DOWN);
            vs.Z -= 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[3])) {
            //referee->move(this->_id, MOVE_LEFT );
            vs.X -= 2.0f;
        }
        if (receiver.isKeyDown(this->_keyMap[4]) && _anim != JUMP) {
            //referee->placeBomb(this->_id);
            vs.Y += 10.0f;
            _mesh->setMD2Animation(irr::scene::EMAT_JUMP);
            _mesh->setLoopMode(false);
            _anim = JUMP;
        } else if (_anim == JUMP) {
            irr::core::list<irr::scene::ISceneNodeAnimator *>::ConstIterator itAnim = _mesh->getAnimators().begin();
            irr::scene::ISceneNodeAnimatorCollisionResponse *animator = static_cast<irr::scene::ISceneNodeAnimatorCollisionResponse *>(*itAnim);
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
    _mesh->addAnimator(animator);
}

irr::scene::IAnimatedMeshSceneNode * Player::getMesh() const {
    return _mesh;
}

irr::core::vector3df Player::getPosition() const {
    return _mesh->getPosition();
}

void
Player::setCtrllrId(irr::u8 const &id) {
    this->_ctrllrId = id;
}

void
Player::setUsingCtrllr(const bool state) {
    this->_isUsingCtrllr = state;
}

irr::s8
Player::getCtrllrId() const {
    return this->_ctrllrId;
}

bool
Player::getIsUsingCtrllr() const {
    return this->_isUsingCtrllr;
}
