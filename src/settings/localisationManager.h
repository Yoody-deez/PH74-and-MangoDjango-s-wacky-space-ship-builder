#pragma once

#include <unordered_map>
#include <string>

using namespace std;

/**
 * @brief Gestionnaire de la localisation et des traductions dans le jeu. Classe en singleton.
 */
class LocalisationManager
{
private:
    unordered_map<string, string> translations;
    string currentLanguage;

    LocalisationManager();

    ~LocalisationManager();
    

    LocalisationManager& operator=(const LocalisationManager&) = delete;
    LocalisationManager(const LocalisationManager&) = delete;

public:
    static LocalisationManager& getInstance();

    bool setLanguage(const string& language);

    string getTranslation(const string& key) const;
};