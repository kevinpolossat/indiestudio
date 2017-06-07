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
#include "ResourceManager.hh"

MenuMainPage::MenuMainPage() {
    ResourceManager::loadAnimatedMesh("Bomberman.obj", "./assets/Bomberman/");
    ResourceManager::loadAnimatedMesh("bomb.obj", "./assets/bomb/");
    this->_frame = 0;
}

MenuMainPage::~MenuMainPage() {

}

bool
MenuMainPage::setScene() {
    this->unsetScene();
    this->_bombIdx = 0;
    this->_rotation = 0;
    this->_frame = 0;
    ResourceManager::device()->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -10), irr::core::vector3df(0, 0, 0));

    irr::scene::IAnimatedMesh    *bombermanMesh = ResourceManager::getAnimatedMesh("Bomberman.obj");
    irr::scene::IAnimatedMesh    *bombMesh = ResourceManager::getAnimatedMesh("bomb.obj");
    if (!bombermanMesh) {
        ResourceManager::device()->drop();
        return false;
    }
    this->_bombermanNode = ResourceManager::device()->getSceneManager()->addAnimatedMeshSceneNode(bombermanMesh);

    if (!bombMesh) {
        ResourceManager::device()->drop();
        return false;
    }
    this->_bombNode = ResourceManager::device()->getSceneManager()->addAnimatedMeshSceneNode(bombMesh);

    if (this->_bombermanNode) {
        this->_bombermanNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_bombermanNode->setMD2Animation(irr::scene::EMAT_STAND);
        this->_bombermanNode->setPosition(irr::core::vector3df(3.45f, -2.25f, -5.5f));
    }
    if (this->_bombNode) {
        this->_bombNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_bombNode->setMD2Animation(irr::scene::EMAT_STAND);
        this->_bombNode->setPosition(irr::core::vector3df(0,0,2));
    }
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);
    this->_title = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(300, 0, 1258 + 300, 425), 0, -1, NULL);
    this->_title->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Bomberman.png"));
    this->_title->setUseAlphaChannel(true);
    this->_title->setDrawBorder(false);
    this->_title->setEnabled(false);

    this->_start = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(610, 316 + 50, 1310, 470 + 50), 0, -1, NULL);
    this->_start->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Start_700x155.png"));
    this->_start->setUseAlphaChannel(true);
    this->_start->setDrawBorder(false);

    this->_settings = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(610, 470 + 50, 1310, 625 + 50), 0, -1, NULL);
    this->_settings->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Settings_700x155.png"));
    this->_settings->setUseAlphaChannel(true);
    this->_settings->setDrawBorder(false);

    this->_credit = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(610, 625 + 50, 1310, 780 + 50), 0, -1, NULL);
    this->_credit->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Credit_700x155.png"));
    this->_credit->setUseAlphaChannel(true);
    this->_credit->setDrawBorder(false);

    this->_quit = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(610, 780 + 50, 1310, 935 + 50), 0, -1, NULL);
    this->_quit->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Leave_700x155.png"));
    this->_quit->setUseAlphaChannel(true);
    this->_quit->setDrawBorder(false);

    this->_bombNode->setPosition(irr::core::vector3df(-8, .5, 2));
    this->_time = ResourceManager::device()->getTimer()->getTime();
    return true;
}

int
MenuMainPage::refresh(int &menuState) {
    this->_bombermanNode->setRotation(irr::core::vector3df(0, -this->_rotation, 0));
    //this->_bombNode->setRotation(irr::core::vector3df(this->_rotation, -this->_rotation, this->_rotation));

    const irr::u32 now = ResourceManager::device()->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;
    if (this->_frame > 10) {
        if (isMouseOnStart()) {
            this->_bombNode->setPosition(irr::core::vector3df(-8, .5, 2));
            this->_bombIdx = 0;
            if (ResourceManager::eventHandler().isMouseLeftClickPressed()) {
                this->unsetScene();
                menuState = MENUGAMEMODE;
                return 1;
            }
        } else if (isMouseOnSettings()) {
            this->_bombNode->setPosition(irr::core::vector3df(-8, -3.125f, 2));
            this->_bombIdx = 1;
            if (ResourceManager::eventHandler().isMouseLeftClickPressed()) {
                this->unsetScene();
                menuState = MENUSETTINGSPAGE;
                return 1;
            }
        } else if (isMouseOnCredit()) {
            this->_bombNode->setPosition(irr::core::vector3df(-8, -3.125f, 2));
            this->_bombIdx = 1;
            if (ResourceManager::eventHandler().isMouseLeftClickPressed()) {
                this->unsetScene();
                menuState = MENUCREDITPAGE;
                return 1;
            }
        } else if (isMouseOnLeave()) {
            this->_bombNode->setPosition(irr::core::vector3df(-8, -6.75f, 2));
            this->_bombIdx = 2;
            if (ResourceManager::eventHandler().isMouseLeftClickPressed()) {
                return 0;
            }
        }
    }
    if (frameDeltaTime > 0.05) {
        this->_time = now;
        if (ResourceManager::eventHandler().isKeyDown(irr::KEY_UP)) {
            if (this->_bombIdx) {
                irr::core::vector3df bombPos = this->_bombNode->getPosition();
                bombPos.Y += 3.625;
                this->_bombNode->setPosition(bombPos);
                this->_bombIdx -= 1;
            } else {
                this->_bombNode->setPosition(irr::core::vector3df(-8, -6.75f, 2));
                this->_bombIdx = 2;
            }
        } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_DOWN)) {
            if (this->_bombIdx < 2) {
                irr::core::vector3df bombPos = this->_bombNode->getPosition();
                bombPos.Y -= 3.625;
                this->_bombNode->setPosition(bombPos);
                this->_bombIdx += 1;
            } else {
                this->_bombNode->setPosition(irr::core::vector3df(-8, .5, 2));
                this->_bombIdx = 0;
            }
        } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN)) {
            if (!this->_bombIdx) {
                this->unsetScene();
                menuState = MENUGAMEMODE;
                return 1;
            } else if (this->_bombIdx == 1) {
                this->unsetScene();
                menuState = MENUSETTINGSPAGE;
                return 1;
            } else if (this->_bombIdx == 2) {
                return 0;
            }
        } else if (_frame > 10 && ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
            return 0;
        }
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    this->_rotation = (this->_rotation + 1) % 360;
    if (this->_frame < 11)
        this->_frame += 1;
    return 2;
}

void
MenuMainPage::unsetScene() {
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}

bool
MenuMainPage::isMouseOnStart() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= 610 && mousePos.X <= 1310 && mousePos.Y > 366 && mousePos.Y < 520;
}

bool
MenuMainPage::isMouseOnSettings() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= 610 && mousePos.X <= 1310 && mousePos.Y > 520 && mousePos.Y < 675;
}

bool
MenuMainPage::isMouseOnCredit() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= 610 && mousePos.X <= 1310 && mousePos.Y > 675 && mousePos.Y < 820;
}


bool
MenuMainPage::isMouseOnLeave() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= 610 && mousePos.X <= 1310 && mousePos.Y > 820 && mousePos.Y < 985;
}