//
// Created by kevin on 17/05/17.
//

#include "Action.hh"

Action::Action(int id, Action::Type t, float speed): _type(t), _id(id), _speed(speed) {

}

Action::~Action() {

}

Action::Action(Action const &other) {
    _type   = other._type;
    _id     = other._id;
    _speed  = other._speed;
}

Action::Action(Action && other) {
    _type   = other._type;
    _id     = other._id;
    _speed  = other._speed;
}

Action &Action::operator=(Action const &other) {
    _type   = other._type;
    _id     = other._id;
    _speed  = other._speed;
    return *this;
}

Action::Type Action::type() const {
    return _type;
}

Action::Id Action::id() const {
    return _id;
}

float Action::speed() const {
    return _speed;
}
