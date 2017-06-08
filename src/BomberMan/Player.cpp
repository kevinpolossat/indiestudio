#include <Client.hh>
#include "Player.hh"

Player::Player(uint8_t const id,
               std::array<irr::EKEY_CODE, 5> keyMap,
               irr::core::vector3df const & scale)
        : _node(scale),
          _id(id),
          _keyMap(keyMap),
          _ctrllrId(-1),
          _isUsingCtrllr(false)
{
}

Player::Player(Player const & other)
        : _node(other._node),
          _id(other._id),
          _keyMap(other._keyMap),
          _ctrllrId(other.getCtrllrId()),
          _isUsingCtrllr(other.getIsUsingCtrllr())
{

}

Player::Player(Player const && other)
        : _node(other._node),
          _id(other._id),
          _keyMap(other._keyMap),
          _ctrllrId(other.getCtrllrId()),
          _isUsingCtrllr(other.getIsUsingCtrllr())
{

}

Player::~Player() {
}

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

void Player::_sendAction(Action const & action) {
    std::stringstream ofs;
    boost::archive::text_oarchive oa(ofs, boost::archive::no_header);;
    oa << action;
    Client::getClient().send(ofs.str());
}

void Player::move(EventHandler const & receiver, Referee & ) {
    if (!this->_isUsingCtrllr) {
        if (receiver.isKeyDown(this->_keyMap[0])) {
            _sendAction(Action(this->_id, Action::UP, 0));
        }
        if (receiver.isKeyDown(this->_keyMap[1])) {
            _sendAction(Action(this->_id, Action::RIGHT, 0));
        }
        if (receiver.isKeyDown(this->_keyMap[2])) {
            _sendAction(Action(this->_id, Action::DOWN, 0));
        }
        if (receiver.isKeyDown(this->_keyMap[3])) {
            _sendAction(Action(this->_id, Action::LEFT, 0));
        }
        if (receiver.isKeyDown(this->_keyMap[4])) {
            _sendAction(Action(this->_id, Action::BOMB, 0));
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

int32_t
Player::getCtrllrId() const {
    return this->_ctrllrId;
}

bool
Player::getIsUsingCtrllr() const {
    return this->_isUsingCtrllr;
}

PlayerNode & Player::getNode() {
    return _node;
}

uint32_t Player::getId() const {
    return _id;
}

