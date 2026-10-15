#pragma once

#include <string>
#include "settings.h"

using namespace std;

class Engine {
private:
    bool isRunning;
    Settings settings;

    Engine();
    ~Engine();

    Engine(const Engine&);
    Engine& operator=(const Engine&);

public:
    static Engine& getInstance();

    void init(const string& configPath);

    void run();

    void stop();

    // Récupérer les paramètres
    Settings& getSettings();

    void saveSettings(const string& configPath);

    bool getIsRunning() const;
};