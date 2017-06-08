//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_SETTINGS_HH
#define INDIESTUDIO_SETTINGS_HH

class Settings {
public:
    ~Settings();

    static int &music_volume();
    static int &sound_volume();
private:
    explicit Settings(int mv = 10, int sv = 10);
    Settings(Settings const &other)                 = delete;
    Settings(Settings &&other)                      = delete;

    Settings    &operator = (Settings const &other) = delete;
    static      Settings &instance();

    int         _music_volume;
    int         _sound_volume;

    int         &music_volume_impl();
    int         &sound_volume_impl();
};


#endif //INDIESTUDIO_SETTINGS_HH
