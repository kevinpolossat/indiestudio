/*
** AMenuScene.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/AMenuScene.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 11:16:06 2017 Charles Fraïssé
** Last update Mon May 15 11:16:06 2017 Charles Fraïssé
*/

#ifndef INDIESTUDIO_SCENE_HH
#define INDIESTUDIO_SCENE_HH

#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "EventReceiver.hh"

class                           Scene {
protected:
    irr::video::IVideoDriver    *_driver;
    irr::scene::ISceneManager   *_smgr;
    irr::gui::IGUIEnvironment   *_gui;

public:
    Scene(irr::IrrlichtDevice *);
    virtual ~Scene();

    virtual bool                setScene(irr::IrrlichtDevice *);
    virtual int                 refresh(irr::IrrlichtDevice *, int *, EventReceiver *);
    virtual void                unsetScene();
};


#endif //INDIESTUDIO_SCENE_HH
