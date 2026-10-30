#pragma once
#include <string>

class ConfigManager {
private:
    int languageIndex;
    int resolutionIndex;
    bool fullscreen;
    bool vsync;
    float mouseSensitivity;
    float fov;

    ConfigManager();

    std::string extractTagValue(const std::string& line, const std::string& tag);

public:
    static ConfigManager& getInstance();

    bool loadFromFile(const std::string& filepath);

    void saveToFile(const std::string& filepath);

    int getLanguageIndex() const;
    void setLanguageIndex(int val);

    int getResolutionIndex() const;
    void setResolutionIndex(int val);

    bool isFullscreen() const;
    void setFullscreen(bool val);

    bool isVsync() const;
    void setVsync(bool val);

    float getMouseSensitivity() const;
    void setMouseSensitivity(float val);

    float getFov() const;
    void setFov(float val);
};