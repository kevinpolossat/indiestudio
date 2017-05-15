//
// Created by beurie_v on 12/05/17.
//

#include "LEventReceiver.hh"

LEventReceiver::LEventReceiver(std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>> const &nModels,
                               std::vector<std::array<irr::EKEY_CODE, 5>> const &keyMap)
        : AEventReceiver(nModels, keyMap) {

}

LEventReceiver::~LEventReceiver() {

}

bool
LEventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown) {
        if (this->_nModels.size() > 0) {
            if (event.KeyInput.Key == this->_keyMap[0][0]) {
                std::cout << "Player1 moveUp" << std::endl;
                //this->_nModels[0]->moveUp();
            } else if (event.KeyInput.Key == this->_keyMap[0][1]) {
                std::cout << "Player1 moveRight" << std::endl;
                //this->_nModels[0]->moveRight();
            } else if (event.KeyInput.Key == this->_keyMap[0][2]) {
                std::cout << "Player1 moveDown" << std::endl;
                //this->_nModels[0]->moveDown();
            } else if (event.KeyInput.Key == this->_keyMap[0][3]) {
                std::cout << "Player1 moveLeft" << std::endl;
                //this->_nModels[0]->moveLeft();
            } else if (event.KeyInput.Key == this->_keyMap[0][4]) {
                std::cout << "Player1 placeBomb" << std::endl;
                //this->_nModels[0]->placeBomb();
            }
        }

        if (this->_nModels.size() > 1) {
            if (event.KeyInput.Key == this->_keyMap[1][0]) {
                std::cout << "Player2 moveUp" << std::endl;
                //this->_nModels[1]->moveUp();
            } else if (event.KeyInput.Key == this->_keyMap[1][1]) {
                std::cout << "Player2 moveRight" << std::endl;
                //this->_nModels[1]->moveRight();
            } else if (event.KeyInput.Key == this->_keyMap[1][2]) {
                std::cout << "Player2 moveDown" << std::endl;
                //this->_nModels[1]->moveDown();
            } else if (event.KeyInput.Key == this->_keyMap[1][3]) {
                std::cout << "Player2 moveLeft" << std::endl;
                //this->_nModels[1]->moveLeft();
            } else if (event.KeyInput.Key == this->_keyMap[1][4]) {
                std::cout << "Player2 placeBomb" << std::endl;
                //this->_nModels[1]->placeBomb();
            }
        }
    }
}
