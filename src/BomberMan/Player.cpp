#include "Player.hh"

Player::Player(uint8_t const id,
               std::array<irr::EKEY_CODE, 5> keyMap,
               irr::core::vector3df const & scale)
        : _node(scale),
          _id(id),
          _keyMap(keyMap),
          _ctrllrId(-1)
{
}

Player::Player(Player const & other)
        : _node(other.getNode()),
          _id(other._id),
          _keyMap(other._keyMap),
          _ctrllrId(other.getCtrllrId()),
          _isUsingCtrllr(other.getIsUsingCtrllr())
{

}

Player::Player(Player const && other)
        : _node(other.getNode()),
          _id(other._id),
          _keyMap(other._keyMap),
          _ctrllrId(other.getCtrllrId()),
          _isUsingCtrllr(other.getIsUsingCtrllr())
{

}

Player::~Player() {

}

void Player::move(EventHandler const & receiver, Referee & referee) {
    bool moved = false;
    if (!this->_isUsingCtrllr) {
        if (receiver.isKeyDown(this->_keyMap[0])) {
            referee.doAction(this->_id, Action::UP, 0);
            moved = true;
        }
        if (receiver.isKeyDown(this->_keyMap[1])) {
            referee.doAction(this->_id, Action::RIGHT, 0);
            moved = true;
        }
        if (receiver.isKeyDown(this->_keyMap[2])) {
            referee.doAction(this->_id, Action::DOWN, 0);
            moved = true;
        }
        if (receiver.isKeyDown(this->_keyMap[3])) {
            referee.doAction(this->_id, Action::LEFT, 0);
            moved = true;
        }
        if (receiver.isKeyDown(this->_keyMap[4])) {
            referee.doAction(this->_id, Action::BOMB, 0);
        }
//        if (moved) {
//            if (_anim != RUN) {
//                _node->setMD2Animation(irr::scene::EMAT_RUN);
//                _node->setLoopMode(true);
//                _anim = RUN;
//            }
//        } else {
//            if (_anim != STAND) {
//                _node->setMD2Animation(irr::scene::EMAT_STAND);
//                _node->setLoopMode(true);
//                _anim = STAND;
//            }
//        }
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

PlayerNode & Player::getNode() {
    return _node;
}

PlayerNode const &Player::getNode() const {
    return _node;
}

