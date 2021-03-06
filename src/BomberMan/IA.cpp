//
// Created by vincent on 5/31/17.
//

#include "IA.hh"

static IA *ref[4] = {nullptr};

IA::IA() : _node(irr::core::vector3df(0.f, 0.f, 0.f)),
           _id(0),
           _lua(luaL_newstate()),
           _mem(Action::WAIT),
           _dist(0.f),
           _depth(DEFAULT_AI_DEPTH) {
    this->initBinding();
    ref[this->_id] = this;
}

IA::IA(uint32_t id, irr::core::vector3df const & scale, size_t depth)
        : _node(scale),
          _id(id),
          _lua(luaL_newstate()),
          _mem(Action::WAIT),
          _dist(0.f),
          _depth(depth) {
    this->initBinding();
    ref[this->_id] = this;
}

IA::IA(IA const &&other)
        : _node(other._node),
          _id(other._id),
          _lua(other._lua),
          _mem(other._mem),
          _dist(other._dist),
          _depth(other._depth) {
    ref[this->_id] = this;
}

IA::IA(IA const &other)
        : _node(other._node),
          _id(other._id),
          _lua(other._lua),
          _mem(other._mem),
          _dist(other._dist),
          _depth(other._depth) {
    ref[this->_id] = this;
}

IA::~IA() {
}

size_t copy(size_t me, size_t id) {
    return ref[me]->copyFromRefereeId(id);
}

bool amIDead(size_t me, size_t id) {
    return ref[me]->amIDeadFromId(id);
}

size_t getNumberOfBoxes(size_t me, size_t id) {
    return ref[me]->getNumberOfBoxesFromId(id);
}

size_t getNumberOfPlayer(size_t me, size_t id) {
    return ref[me]->getNumberOfPlayerFromId(id);
}

void doAction(size_t me, size_t id, size_t action) {
    ref[me]->doActionFromId(id, action);
}

void doUpdate(size_t me, size_t id, size_t nums) {
    ref[me]->doUpdateFromId(id, nums);
}

size_t getNumberOfPowerUp(size_t me, size_t id) {
    return ref[me]->getNumberOfPowerUpFromId(id);
}

size_t getMaxDepth(size_t me) {
    return ref[me]->getMaxDepth();
}

bool isActionPossible(size_t me, size_t id, size_t action) {
    return ref[me]->isActionPossible(id, action);
}

void IA::initBinding() {
    luaL_openlibs(this->_lua);
    luaL_dofile(this->_lua, (ResourceManager::assets_rela + "script/brain_logic.lua").c_str());
    lua_pcall(this->_lua, 0, 0, 0);
    luabridge::getGlobalNamespace(this->_lua)
            .addFunction("copy", copy)
            .addFunction("amIDead", amIDead)
            .addFunction("getNumberOfBoxes", getNumberOfBoxes)
            .addFunction("getNumberOfPlayer", getNumberOfPlayer)
            .addFunction("doAction", doAction)
            .addFunction("doUpdate", doUpdate)
            .addFunction("getNumberOfPowerUp", getNumberOfPowerUp)
            .addFunction("getMaxDepth", ::getMaxDepth)
            .addFunction("isActionPossible", ::isActionPossible);
}

Action IA::move(EventHandler const &, Referee & referee) {
    if (this->_dist == 0.f) {
        this->_referees.clear();
        this->_referees.push_back(referee);

        luabridge::LuaRef func = luabridge::getGlobal(this->_lua, "brain");
        int result = func(this->_id).cast<int>();
        switch (result) {
            case 0:
                this->_mem = Action::BOMB;
                break;
            case 1:
                this->_mem = Action::UP;
                this->_node.setOrientation(6);
                break;
            case 2:
                this->_mem = Action::RIGHT;
                this->_node.setOrientation(0);
                break;
            case 3:
                this->_mem = Action::DOWN;
                this->_node.setOrientation(2);
                break;
            case 4:
                this->_mem = Action::LEFT;
                this->_node.setOrientation(4);
                break;
            default:
                this->_mem = Action::WAIT;
        }
    }
    if (this->_mem != Action::WAIT and this->_mem != Action::BOMB) {
        auto c = referee.getCharacters();
        auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
        this->_dist += me->getSpeed() * SPEED_UNIT;
        if (this->_dist >= 1.f)
            this->_dist = 0.f;
        this->_node.setAnimation(PlayerNode::RUN);
    } else {
        this->_node.setAnimation(PlayerNode::STAND);
    }
    return Action(this->getId(), this->_mem, 0);
}

PlayerNode & IA::getNode() {
    return _node;
}

uint32_t IA::getId() const {
    return _id;
}

size_t IA::copyFromRefereeId(size_t id) {
    this->_referees.push_back(this->_referees[id]);
    return this->_referees.size() - 1;
}

bool IA::amIDeadFromId(size_t id) const {
    auto c = this->_referees[id].getCharacters();
    return std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); }) == c.end();
}

size_t IA::getNumberOfBoxesFromId(size_t id) const {
    return this->_referees[id].getMap().getBoxes().size();
}

size_t IA::getNumberOfPlayerFromId(size_t id) const {
    return this->_referees[id].getCharacters().size();
}

void IA::doActionFromId(size_t id, size_t action) {
    switch (action) {
        case 0:
            this->_referees[id].doAction(Action(this->getId(), Action::BOMB, 0));
            break;
        case 1:
            this->_referees[id].doAction(Action(this->getId(), Action::UP, 1));
            break;
        case 2:
            this->_referees[id].doAction(Action(this->getId(), Action::RIGHT, 1));
            break;
        case 3:
            this->_referees[id].doAction(Action(this->getId(), Action::DOWN, 1));
            break;
        case 4:
            this->_referees[id].doAction(Action(this->getId(), Action::LEFT, 1));
            break;
        default:
            break;
    }
}

void IA::doUpdateFromId(size_t id, size_t nums) {
    auto c = this->_referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    if (nums == 0)
        this->_referees[id].update(false, 1 / (me->getSpeed() * SPEED_UNIT) + 20);
    else
        this->_referees[id].update(false, nums);
}

size_t IA::getNumberOfPowerUpFromId(size_t id) const {
    auto c = this->_referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    return me->getBonusTaken();
}

size_t IA::getMaxDepth() const {
    return this->_depth;
}

bool IA::isActionPossible(size_t id, size_t action) const {
    auto c = this->_referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    auto const &x = me->getPosition().X;
    auto const &y = me->getPosition().Y;
    auto const &z = me->getPosition().Z;

    irr::core::vector3df    pos;
    switch (action) {
        case 1:
            pos = irr::core::vector3df(x, y, z - 1);
            break;

        case 2:
            pos = irr::core::vector3df(x - 1, y, z);
            break;

        case 3:
            pos = irr::core::vector3df(x, y, z + 1);
            break;

        case 4:
            pos = irr::core::vector3df(x + 1, y, z);
            break;

        default:
            break;
    }
    return this->_referees[id].isCellAvailable(pos);
}

bool IA::isHuman() const {
    return false;
}
