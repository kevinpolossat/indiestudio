/*
** MenuGameMode.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuGameMode.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 29 16:18:26 2017 Charles Fraïssé
** Last update Mon May 29 16:18:26 2017 Charles Fraïssé
*/
#ifndef INDIESTUDIO_MENUGAMEMODE_HH
#define INDIESTUDIO_MENUGAMEMODE_HH

#include "IScene.hh"

class                       MenuGameMode : public IScene {
private:
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_back;
    irr::gui::IGUIButton                *_online;
    irr::gui::IGUIButton                *_local;

public:
    explicit MenuGameMode();
    virtual ~MenuGameMode();

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};


#endif //INDIESTUDIO_MENUGAMEMODE_HH
