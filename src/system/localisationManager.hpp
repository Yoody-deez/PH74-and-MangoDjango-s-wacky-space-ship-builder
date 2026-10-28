#include "localisationManager.h"
#include <fstream>

LocalisationManager::LocalisationManager() {}
LocalisationManager::~LocalisationManager() {}

string LocalisationManager::getTranslation(const std::string& key) const{
    auto it = translations.find(key);

    if (it != translations.end())
        return it->second;

    return "[MISSING: " + key + "]";
}

bool LocalisationManager::setLanguage(const string& language){
    // language doit être un code de deux caractères de long.
    if (language.length() != 2) return false;

    // TODO: Parcourir les fichiers.
}