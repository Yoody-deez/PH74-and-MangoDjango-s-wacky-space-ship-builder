#pragma once

#include <string>
#include <map>

using namespace std;

class Settings {
public:
    std::map<string, string> data;

    bool load(const string& filePath);

    bool save(const string& filePath);

    string get(const string& key, const string& defaultValue = "") const;

    // Définir une valeur
    void set(const string& key, const string& value);
};