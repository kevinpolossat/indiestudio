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
    int                                 _frame;
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    int                                 _idx;
    irr::u32                            _time;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_back;
    irr::gui::IGUIButton                *_online;
    irr::gui::IGUIButton                *_local;
    irr::gui::IGUIComboBox              *_box;
    irr::gui::IGUIFont                  *_font;



public:
    explicit MenuGameMode();
    virtual ~MenuGameMode();

    MenuGameMode(MenuGameMode const &other)                 = delete;
    MenuGameMode(MenuGameMode &&other)                      = delete;
    MenuGameMode &operator = (MenuGameMode const &other)    = delete;

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENUGAMEMODE_HH
