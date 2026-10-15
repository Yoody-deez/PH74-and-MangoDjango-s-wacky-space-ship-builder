#pragma once

#include <string>
#include "settings.h"

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

    void init(const std::string& configPath);

    void run();

    void stop();

    // Récupérer les paramètres
    Settings& getSettings();

    void saveSettings(const std::string& configPath);

    bool getIsRunning() const;
};