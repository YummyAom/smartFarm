#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

struct UserSettings
{
    float targetLux;
    float targetHumidity;
    int targetTemp;
    int targetSoilMoisture;

    bool fanEnabled;
    bool pumpEnabled;
    bool ledEnabled;
};

#endif
