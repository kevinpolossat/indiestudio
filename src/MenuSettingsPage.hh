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

#include "IScene.hh"
#include "EventHandler.hh"

class                                   MenuSettingsPage : public IScene {
private:
    int                                 _vpad;
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_back;
    irr::gui::IGUIButton                *_reset;
    irr::gui::IGUIButton                *_player1Bomb;
    irr::gui::IGUIButton                *_player1BombKey;
    irr::gui::IGUIButton                *_player2Bomb;
    irr::gui::IGUIButton                *_player2BombKey;
    irr::gui::IGUIButton                *_player1Right;
    irr::gui::IGUIButton                *_player1RightKey;
    irr::gui::IGUIButton                *_player2Right;
    irr::gui::IGUIButton                *_player2RightKey;
    irr::gui::IGUIButton                *_player1Left;
    irr::gui::IGUIButton                *_player1LeftKey;
    irr::gui::IGUIButton                *_player2Left;
    irr::gui::IGUIButton                *_player2LeftKey;
    irr::gui::IGUIButton                *_player1Down;
    irr::gui::IGUIButton                *_player1DownKey;
    irr::gui::IGUIButton                *_player2Down;
    irr::gui::IGUIButton                *_player2DownKey;
    irr::gui::IGUIButton                *_player1Up;
    irr::gui::IGUIButton                *_player1UpKey;
    irr::gui::IGUIButton                *_player2Up;
    irr::gui::IGUIButton                *_player2UpKey;
    irr::gui::IGUIButton                *_player1Title;
    irr::gui::IGUIButton                *_player2Title;


    bool                    isMouseOnBack() const;
    bool                    isMouseOnReset() const;

public:
    explicit MenuSettingsPage();
    virtual ~MenuSettingsPage();

    virtual bool            setScene();
    virtual int             refresh(int *);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENUSETTINGSPAGE_HH
