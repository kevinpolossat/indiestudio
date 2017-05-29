//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_SETTINGS_HH
#define INDIESTUDIO_SETTINGS_HH

class Settings {
public:
    ~Settings();

private:
    explicit Settings();
    Settings(Settings const &other)                 = delete;
    Settings(Settings &&other)                      = delete;
    Settings &operator = (Settings const &other)    = delete;
    Settings &instance();
};


#endif //INDIESTUDIO_SETTINGS_HH
