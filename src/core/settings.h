#pragma once
#include <string>
#include <map>

class Settings {
public:
    std::map<std::string, std::string> data;

    bool load(const std::string& filePath);

    bool save(const std::string& filePath);

    std::string get(const std::string& key, const std::string& defaultValue = "") const;

    // Définir une valeur
    void set(const std::string& key, const std::string& value);
};