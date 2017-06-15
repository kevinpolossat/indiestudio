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

#include <vector>
#include "IScene.hh"
#include "EventHandler.hh"

class                                   MenuSettingsPage : public IScene {
private:
    int                                 _vpad;
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    int                                 _musicVolumeIdx;
    int                                 _effectVolumeIdx;
    std::vector<std::string>            _volumePath;
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
    irr::gui::IGUIButton                *_effectVolumeTitle;
    irr::gui::IGUIButton                *_effectVolume;
    irr::gui::IGUIButton                *_effectVolumeUP;
    irr::gui::IGUIButton                *_effectVolumeDOWN;
    irr::gui::IGUIButton                *_musicVolumeTitle;
    irr::gui::IGUIButton                *_musicVolume;
    irr::gui::IGUIButton                *_musicVolumeUP;
    irr::gui::IGUIButton                *_musicVolumeDOWN;
    bool                                _wfkP1Up;
    bool                                _wfkP1Right;
    bool                                _wfkP1Down;
    bool                                _wfkP1Left;
    bool                                _wfkP1Bomb;
    bool                                _wfkP2Up;
    bool                                _wfkP2Right;
    bool                                _wfkP2Down;
    bool                                _wfkP2Left;
    bool                                _wfkP2Bomb;

    bool                    isMouseOnBack() const;
    bool                    isMouseOnReset() const;
    bool                    _isKeyFree(uint32_t const, uint32_t const, irr::EKEY_CODE const) const;

public:
    explicit MenuSettingsPage();
    virtual ~MenuSettingsPage();

    MenuSettingsPage(MenuSettingsPage const & other)                = delete;
    MenuSettingsPage(MenuSettingsPage &&other)                      = delete;
    MenuSettingsPage &operator = (MenuSettingsPage const & other)   = delete;

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};

#endif //INDIESTUDIO_MENUSETTINGSPAGE_HH
