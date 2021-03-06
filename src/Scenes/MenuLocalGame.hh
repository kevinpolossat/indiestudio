/*
** MenuLocalGame.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuLocalGame.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Tue May 30 10:43:38 2017 Charles Fraïssé
** Last update Tue May 30 10:43:38 2017 Charles Fraïssé
*/
#ifndef INDIESTUDIO_MENULOCALGAME_HH
#define INDIESTUDIO_MENULOCALGAME_HH

#include "IScene.hh"

class                       MenuLocalGame : public IScene {
private:
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    bool                                _isP2IA;
    int                                 _frame;
    irr::u32                            _time;
    irr::gui::IGUIButton                *_bg;
    irr::gui::IGUIButton                *_back;
    irr::gui::IGUIButton                *_confirm;
    irr::gui::IGUIButton                *P1Picture;
    irr::gui::IGUIButton                *P1Role;
    irr::gui::IGUIButton                *P2Picture;
    irr::gui::IGUIButton                *P2Role;
    irr::gui::IGUIButton                *P2RoleLeft;
    irr::gui::IGUIButton                *P2RoleRight;
    irr::gui::IGUIButton                *P3RoleLeft;
    irr::gui::IGUIButton                *P3RoleRight;
    irr::gui::IGUIButton                *P3Picture;
    irr::gui::IGUIButton                *P3Role;
    irr::gui::IGUIButton                *P4Picture;
    irr::gui::IGUIButton                *P4Role;
    irr::gui::IGUIButton                *P4RoleLeft;
    irr::gui::IGUIButton                *P4RoleRight;
    int                                 _P2Idx;
    int                                 _P3Idx;
    int                                 _P4Idx;
    std::array<int, 3>                  _IALvl;
    int                                 _idx;
    irr::video::ITexture                *_selector;

public:
    explicit MenuLocalGame();
    virtual ~MenuLocalGame();

    MenuLocalGame(MenuLocalGame const & other)              = delete;
    MenuLocalGame(MenuLocalGame &&other)                    = delete;
    MenuLocalGame &operator = (MenuLocalGame const & other) = delete;

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENULOCALGAME_HH
