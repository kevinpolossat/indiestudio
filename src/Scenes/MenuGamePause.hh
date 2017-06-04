/*
** MenuGamePause.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuGamePause.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Wed May 17 10:22:16 2017 Charles Fraïssé
** Last update Wed May 17 10:22:16 2017 Charles Fraïssé
*/
#ifndef INDIESTUDIO_MENUGAMEPAUSE_HH
#define INDIESTUDIO_MENUGAMEPAUSE_HH

#include "IScene.hh"
#include "EventHandler.hh"

class                                   MenuGamePause : public IScene {
private:
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_resume;
    irr::gui::IGUIButton                *_save;
    irr::gui::IGUIButton                *_settings;
    irr::gui::IGUIButton                *_quit;

    void                    drawGui() const;

public:
    explicit MenuGamePause();
    virtual ~MenuGamePause();

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};


#endif //INDIESTUDIO_MENUGAMEPAUSE_HH
