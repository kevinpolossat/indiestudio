//
// Created by kevin on 17/05/17.
//

#include "Action.hh"

Action::Action(int id, Action::Type t): _id(id), _type(t) {

}

Action::~Action() {

}

Action::Action(Action const &other) {
    _type = other._type;
    _id = other._id;
}

Action::Action(Action && other) {
    _type = other._type;
    _id = other._id;
}

Action &Action::operator=(Action const &other) {
    _type = other._type;
    _id = other._id;
    return *this;
}

Action::Type Action::type() const {
    return _type;
}

Action::Id Action::id() const {
    return _id;
}
