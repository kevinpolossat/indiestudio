//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_IANIMATION_HH
#define INDIESTUDIO_IANIMATION_HH

class IEffect {
public:
    virtual         ~IEffect() {}
    virtual void    update()        = 0;
    virtual bool    isOver() const  = 0;
private:

};

#endif //INDIESTUDIO_IANIMATION_HH
