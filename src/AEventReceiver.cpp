//
// Created by beurie_v on 12/05/17.
//

#include "AEventReceiver.hh"

AEventReceiver::AEventReceiver(std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>> const &nModels,
                               std::vector<std::array<irr::EKEY_CODE, 5>> const &keyMap)
        : _isMoving(false),
          _keyMap(keyMap),
          _nModels(nModels) {

}

AEventReceiver::~AEventReceiver() {

}

bool AEventReceiver::OnEvent(const irr::SEvent &event) {

}