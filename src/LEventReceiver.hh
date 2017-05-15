//
// Created by beurie_v on 12/05/17.
//

#ifndef CPP_LEVENTRECEIVER_HH
#define CPP_LEVENTRECEIVER_HH

#include <iostream>
#include <irrlicht.h>
#include <vector>
#include <memory>
#include "AEventReceiver.hh"

class       LEventReceiver : public AEventReceiver {
public:
    LEventReceiver() = delete;
    LEventReceiver(std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>> const &,
                   std::vector<std::array<irr::EKEY_CODE, 5>> const &);
    LEventReceiver(LEventReceiver const &) = delete;
    virtual ~LEventReceiver();

    LEventReceiver          &operator=(LEventReceiver const &) = delete;

    virtual bool           OnEvent(const irr::SEvent &event);
};


#endif //CPP_LEVENTRECEIVER_HH
