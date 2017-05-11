/*
** MenuMainPage.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuMainPage.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 11:07:53 2017 Charles Fraïssé
** Last update Mon May 15 11:07:53 2017 Charles Fraïssé
*/

#ifndef INDIESTUDIO_MENUMAINPAGE_HH
#define INDIESTUDIO_MENUMAINPAGE_HH

#include "Scene.hh"
#include "EventReceiver.hh"

class                                   MenuMainPage : public Scene {
private:
    int                                 _bombIdx;
    int                                 _rotation;
    irr::scene::IAnimatedMesh           *_bombermanMesh;
    irr::scene::IAnimatedMeshSceneNode  *_bombermanNode;
    irr::scene::IAnimatedMesh           *_bombMesh;
    irr::scene::IAnimatedMeshSceneNode  *_bombNode;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_title;
    irr::gui::IGUIStaticText            *_start;
    irr::gui::IGUIStaticText            *_settings;
    irr::gui::IGUIStaticText            *_leave;
    irr::u32                            _time;

public:
    MenuMainPage(irr::IrrlichtDevice *);
    virtual ~MenuMainPage();

    virtual bool            setScene(irr::IrrlichtDevice *);
    virtual int             refresh(irr::IrrlichtDevice *, int *, EventReceiver *);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENUMAINPAGE_HH
