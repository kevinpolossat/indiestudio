/*
** MenuCreditPage.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuCreditPage.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Wed Jun 07 11:18:50 2017 Charles Fraïssé
** Last update Wed Jun 07 11:18:50 2017 Charles Fraïssé
*/
#ifndef INDIESTUDIO_MENUCREDITPAGE_HH
#define INDIESTUDIO_MENUCREDITPAGE_HH

#include "IScene.hh"

class                                   MenuCreditPage : public IScene {
private:
    int                                 _frame;
    int                                 _hpad;
    int                                 _bHeight;
    int                                 _bWidth;
    irr::gui::IGUIButton                *_bg;
    irr::video::ITexture                *_credit;

public:
    explicit MenuCreditPage();
    virtual ~MenuCreditPage();

    virtual bool            setScene();
    virtual int             refresh(int &);
    virtual void            unsetScene();
};


#endif //INDIESTUDIO_MENUCREDITPAGE_HH
