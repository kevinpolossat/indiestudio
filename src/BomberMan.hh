//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_BOMBERMAN_HH
#define INDIESTUDIO_BOMBERMAN_HH


class BomberMan {
public:
    explicit BomberMan();
    ~BomberMan();

    BomberMan(BomberMan const &);
    BomberMan& operator=(BomberMan const &);
    BomberMan(BomberMan &&)                 = delete;
};


#endif //INDIESTUDIO_BOMBERMAN_HH
