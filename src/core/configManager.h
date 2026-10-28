#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager {
private:
    int languageIndex;
    int resolutionIndex;
    bool fullscreen;
    bool vsync;
    float mouseSensitivity;
    float fov;

    ConfigManager() 
        : languageIndex(0), resolutionIndex(0), fullscreen(false), 
          vsync(true), mouseSensitivity(1.0f), fov(90.0f) {}

    std::string extractTagValue(const std::string& line, const std::string& tag) {
        std::string openTag = "<" + tag + ">";
        std::string closeTag = "</" + tag + ">";
        size_t start = line.find(openTag);
        size_t end = line.find(closeTag);
        if (start != std::string::npos && end != std::string::npos) {
            start += openTag.length();
            return line.substr(start, end - start);
        }
        return "";
    }

public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }

    bool loadFromFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cout << "Fichier de configuration introuvable (" << filepath << "). Utilisation des valeurs par defaut." << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        file.close();

        auto extractVal = [&](const std::string& tag) -> std::string {
            std::string openTag = "<" + tag + ">";
            std::string closeTag = "</" + tag + ">";
            size_t start = content.find(openTag);
            size_t end = content.find(closeTag);
            if (start != std::string::npos && end != std::string::npos) {
                start += openTag.length();
                std::string val = content.substr(start, end - start);
                val.erase(0, val.find_first_not_of(" \t\n\r"));
                val.erase(val.find_last_not_of(" \t\n\r") + 1);
                return val;
            }
            return "";
        };

        std::string val;
        if (!(val = extractVal("Language")).empty()) languageIndex = std::stoi(val);
        if (!(val = extractVal("Resolution")).empty()) resolutionIndex = std::stoi(val);
        if (!(val = extractVal("Fullscreen")).empty()) fullscreen = (val == "true");
        if (!(val = extractVal("VSync")).empty()) vsync = (val == "true");
        if (!(val = extractVal("MouseSensitivity")).empty()) mouseSensitivity = std::stof(val);
        if (!(val = extractVal("FOV")).empty()) fov = std::stof(val);

        std::cout << "Parametres charges avec succes depuis " << filepath << std::endl;
				return true;
    }

    void saveToFile(const std::string& filepath) {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Erreur : Impossible d'ecrire le fichier de configuration " << filepath << std::endl;
            return;
        }

        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<Settings>\n";
        file << "    <Language>" << languageIndex << "</Language>\n";
        file << "    <Resolution>" << resolutionIndex << "</Resolution>\n";
        file << "    <Fullscreen>" << (fullscreen ? "true" : "false") << "</Fullscreen>\n";
        file << "    <VSync>" << (vsync ? "true" : "false") << "</VSync>\n";
        file << "    <MouseSensitivity>" << mouseSensitivity << "</MouseSensitivity>\n";
        file << "    <FOV>" << fov << "</FOV>\n";
        file << "</Settings>\n";

        file.close();
        std::cout << "Parametres sauvegardes dans " << filepath << std::endl;
    }

    int getLanguageIndex() const { return languageIndex; }
    void setLanguageIndex(int val) { languageIndex = val; }

    int getResolutionIndex() const { return resolutionIndex; }
    void setResolutionIndex(int val) { resolutionIndex = val; }

    bool isFullscreen() const { return fullscreen; }
    void setFullscreen(bool val) { fullscreen = val; }

    bool isVsync() const { return vsync; }
    void setVsync(bool val) { vsync = val; }

    float getMouseSensitivity() const { return mouseSensitivity; }
    void setMouseSensitivity(float val) { mouseSensitivity = val; }

    float getFov() const { return fov; }
    void setFov(float val) { fov = val; }
};