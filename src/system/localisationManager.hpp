#include "localisationManager.h"
#include <fstream>

LocalisationManager::LocalisationManager() {}
LocalisationManager::~LocalisationManager() {}

string LocalisationManager::getTranslation(const std::string& key) const
{
    auto it = translations.find(key);

    if (it != translations.end())
        return it->second;

    return "[MISSING: " + key + "]";
}