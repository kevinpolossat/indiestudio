//
// Created by kevin on 30/04/17.
//

#ifndef INDIESTUDIO_SERIALIZABLE_HH
#define INDIESTUDIO_SERIALIZABLE_HH


class Serializable {
public:
    virtual ~Serializable() {}

    virtual void fromJSON()         = 0;
    virtual std::string toJSON()    = 0;
};


#endif //INDIESTUDIO_SERIALIZABLE_HH
