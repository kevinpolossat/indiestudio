/*
** MenuMainPage.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuMainPage.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 11:07:53 2017 Charles Fraïssé
** Last update Mon May 15 11:07:53 2017 Charles Fraïssé
*/

#include "MenuMainPage.hh"
/*
MenuMainPage::MenuMainPage(irr::IrrlichtDevice *device) : Scene(device) {
}

MenuMainPage::~MenuMainPage() {

}

bool
MenuMainPage::setScene(irr::IrrlichtDevice *device) {
    this->_bombIdx = 0;
    this->_rotation = 0;
    this->_smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, -10), irr::core::vector3df(0, 0, 0));

    this->_bombermanMesh = this->_smgr->getMesh("./Bomberman/Bomberman.obj");
    if (!this->_bombermanMesh) {
        device->drop();
        return false;
    }
    this->_bombermanNode = this->_smgr->addAnimatedMeshSceneNode(this->_bombermanMesh);

    this->_bombMesh = this->_smgr->getMesh("./Bomb/bomb.obj");
    if (!this->_bombMesh) {
        device->drop();
        return false;
    }
    this->_bombNode = this->_smgr->addAnimatedMeshSceneNode(this->_bombMesh);

    if (this->_bombermanNode) {
        this->_bombermanNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_bombermanNode->setMD2Animation(irr::scene::EMAT_STAND);
        this->_bombermanNode->setPosition(irr::core::vector3df(3.45, -2.25, -5.5));
    }
    if (this->_bombNode) {
        this->_bombNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_bombNode->setMD2Animation(irr::scene::EMAT_STAND);
        this->_bombNode->setPosition(irr::core::vector3df(0,0,2));
    }

    this->_bg = this->_gui->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(this->_driver->getTexture("BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_title = this->_gui->addButton( irr::core::rect<irr::s32>(300, 0, 1258 + 300, 425), 0, -1, NULL);
    this->_title->setImage(this->_driver->getTexture("Bomberman.png"));
    this->_title->setUseAlphaChannel(true);
    this->_title->setDrawBorder(false);
    this->_start = this->_gui->addStaticText(L"Start", irr::core::rect<irr::s32>(610, 316 + 100, 1310, 470.67 + 100), true, true, 0, -1, true);
    this->_settings = this->_gui->addStaticText(L"Settings", irr::core::rect<irr::s32>(610, 520.67 + 100, 1310, 675.34 + 100), true, true, 0, -1, true);
    this->_leave = this->_gui->addStaticText(L"Leave", irr::core::rect<irr::s32>(610, 725.34 + 100, 1310, 880 + 100), true, true, 0, -1, true);
    this->_bombNode->setPosition(irr::core::vector3df(-8, .5, 2));
    this->_time = device->getTimer()->getTime();
    return true;
}

int
MenuMainPage::refresh(irr::IrrlichtDevice *device, int *menuState, EventReceiver *receiver) {

    this->_bombermanNode->setRotation(irr::core::vector3df(0, -this->_rotation, 0));
    this->_bombNode->setRotation(irr::core::vector3df(this->_rotation, -this->_rotation, this->_rotation));
    this->_driver->beginScene(true, true, irr::video::SColor(90, 230, 229, 200));

    const irr::u32 now = device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;

    if (frameDeltaTime > 0.075) {
        this->_time = now;
        if (receiver->IsKeyDown(irr::KEY_UP)) {
            if (this->_bombIdx) {
                irr::core::vector3df bombPos = this->_bombNode->getPosition();
                bombPos.Y += 3.625;
                this->_bombNode->setPosition(bombPos);
                this->_bombIdx -= 1;
            } else {
                this->_bombNode->setPosition(irr::core::vector3df(-8, -5 - 1.75, 2));
                this->_bombIdx = 2;
            }
        } else if (receiver->IsKeyDown(irr::KEY_DOWN)) {
            if (this->_bombIdx < 2) {
                irr::core::vector3df bombPos = this->_bombNode->getPosition();
                bombPos.Y -= 3.625;
                this->_bombNode->setPosition(bombPos);
                this->_bombIdx += 1;
            } else {
                this->_bombNode->setPosition(irr::core::vector3df(-8, .5, 2));
                this->_bombIdx = 0;
            }
        } else if (receiver->IsKeyDown(irr::KEY_RETURN)) {
            if (!this->_bombIdx) {
                this->unsetScene();
                *menuState = 1;
                return 1;
            } else if (this->_bombIdx == 1) {
                this->unsetScene();
                *menuState = 2;
                return 1;
            } else if (this->_bombIdx == 2) {
                return 0;
            }
        } else if (receiver->IsKeyDown(irr::KEY_ESCAPE)) {
            return 0;
        }
    }

    this->_rotation = (this->_rotation + 1) % 360;
    this->_gui->drawAll();
    this->_smgr->drawAll();
    this->_driver->endScene();
    return 2;
}

void
MenuMainPage::unsetScene() {
    this->_gui->clear();
    this->_smgr->clear();
}*/