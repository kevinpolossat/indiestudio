//
// Created by beurie_v on 12/05/17.
//

#ifndef CPP_AEVENTRECEIVER_HH
#define CPP_AEVENTRECEIVER_HH

#include <iostream>
#include <irrlicht.h>
#include <vector>
#include <array>
#include <memory>

class           AEventReceiver : public irr::IEventReceiver {
protected:
    bool                                                                _isMoving;
    std::vector<std::array<irr::EKEY_CODE, 5>>                          _keyMap;
    std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>>    _nModels;

    AEventReceiver(std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>> const &,
                   std::vector<std::array<irr::EKEY_CODE, 5>> const &);

public:
    AEventReceiver() = delete;
    AEventReceiver(AEventReceiver const &) = delete;
    virtual ~AEventReceiver();

    AEventReceiver      &operator=(AEventReceiver const &) = delete;

    virtual bool       OnEvent(const irr::SEvent &event);
};

#endif //CPP_AEVENTRECEIVER_HH
