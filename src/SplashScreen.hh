/*
** SplashScreen.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/SplashScreen.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Tue May 16 14:53:17 2017 Charles Fraïssé
** Last update Tue May 16 14:53:17 2017 Charles Fraïssé
*/
#ifndef INDIESTUDIO_SPLASHSCREEN_HH
#define INDIESTUDIO_SPLASHSCREEN_HH

#include <SFML/Audio.hpp>
#include "IScene.hh"
#include "EventHandler.hh"

class                                   SplashScreen : public IScene {
private:
    int                                 _frame;
    irr::scene::IAnimatedMeshSceneNode  *_titleNode;
//    sf::Music                           _music;

public:
    explicit SplashScreen();
    virtual ~SplashScreen();

    virtual bool            setScene();
    virtual int             refresh(int *);
    virtual void            unsetScene();
};


#endif //INDIESTUDIO_SPLASHSCREEN_HH
