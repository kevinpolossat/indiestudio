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

#include "IScene.hh"
#include "EventHandler.hh"

class                                   MenuMainPage : public IScene {
private:
    int                                 _bombIdx;
    int                                 _rotation;
    irr::scene::IAnimatedMeshSceneNode  *_bombermanNode;
    irr::scene::IAnimatedMeshSceneNode  *_bombNode;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_title;
    irr::gui::IGUIStaticText            *_start;
    irr::gui::IGUIStaticText            *_settings;
    irr::gui::IGUIStaticText            *_leave;
    irr::u32                            _time;
    int                                 _frame;

    bool                    isMouseOnStart() const;
    bool                    isMouseOnSettings() const;
    bool                    isMouseOnLeave() const;

public:
    explicit MenuMainPage();
    virtual ~MenuMainPage();

    virtual bool            setScene();
    virtual int             refresh(int *);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENUMAINPAGE_HH
