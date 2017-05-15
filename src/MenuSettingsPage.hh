/*
** MenuSettingsPage.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuSettingsPage.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 14:14:49 2017 Charles Fraïssé
** Last update Mon May 15 14:14:49 2017 Charles Fraïssé
*/

#ifndef INDIESTUDIO_MENUSETTINGSPAGE_HH
#define INDIESTUDIO_MENUSETTINGSPAGE_HH

#include "Scene.hh"
#include "EventReceiver.hh"

class                                   MenuSettingsPage : public Scene {
private:
    irr::gui::IGUIButton                *_bg;
    irr::u32                            _time;

public:
    MenuSettingsPage(irr::IrrlichtDevice *);
    virtual ~MenuSettingsPage();

    virtual bool            setScene(irr::IrrlichtDevice *);
    virtual int             refresh(irr::IrrlichtDevice *, int *, EventReceiver *);
    virtual void            unsetScene();
};


#endif //INDIESTUDIO_MENUSETTINGSPAGE_HH
