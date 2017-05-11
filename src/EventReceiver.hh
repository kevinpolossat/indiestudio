/*
** EventReceiver.hh for indiestudio in /home/fraiss_c/rendu/indiestudio/EventReceiver.hh
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Thu May 11 10:39:15 2017 Charles Fraïssé
** Last update Thu May 11 10:39:15 2017 Charles Fraïssé
*/

#ifndef INDIESTUDIO_EVENTRECEIVER_HH
#define INDIESTUDIO_EVENTRECEIVER_HH

#include <irrlicht.h>


class                   EventReceiver : public irr::IEventReceiver {
private:
    bool                _Keys[irr::KEY_KEY_CODES_COUNT];

public:
    EventReceiver();
    EventReceiver(EventReceiver const &) = delete;
    virtual ~EventReceiver();

    EventReceiver       &operator=(EventReceiver const &) = delete;
    virtual bool        OnEvent(const irr::SEvent &);
    virtual bool        IsKeyDown(irr::EKEY_CODE) const;
};


#endif //INDIESTUDIO_EVENTRECEIVER_HH
