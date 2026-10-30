#include "localisationManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <algorithm>

LocalisationManager::LocalisationManager() : currentLanguage("fr") {
		setLanguage("fr");
}

LocalisationManager::~LocalisationManager() {}

LocalisationManager& LocalisationManager::getInstance() {
		static LocalisationManager instance;
		return instance;
}

bool LocalisationManager::setLanguage(const string& language) {
		string lang = language;
		for (auto& c : lang) c = static_cast<char>(tolower(c));

		std::filesystem::path filePath = std::filesystem::path(__FILE__).parent_path() / "localization" / (lang + ".xml");
		
		std::ifstream file(filePath);
		if (!file.is_open()) {
				std::cerr << "[LOCALISATION] Erreur : Impossible d'ouvrir le fichier de langue : " << filePath.string() << std::endl;
				return false;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content = buffer.str();
		file.close();

		translations.clear();
		currentLanguage = lang;

		size_t pos = 0;
		while ((pos = content.find("<Text id=\"", pos)) != std::string::npos) {
				size_t idStart = pos + 10;
				size_t idEnd = content.find("\"", idStart);
				if (idEnd == std::string::npos) break;

				string key = content.substr(idStart, idEnd - idStart);

				size_t valStart = content.find(">", idEnd);
				if (valStart == std::string::npos) break;
				valStart++; 

				size_t valEnd = content.find("</Text>", valStart);
				if (valEnd == std::string::npos) break;

				string value = content.substr(valStart, valEnd - valStart);

				while (!value.empty() && (value.front() == ' ' || value.front() == '\n' || value.front() == '\r' || value.front() == '\t')) {
						value.erase(value.begin());
				}
				while (!value.empty() && (value.back() == ' ' || value.back() == '\n' || value.back() == '\r' || value.back() == '\t')) {
						value.pop_back();
				}

				translations[key] = value;
				pos = valEnd + 7;
		}

		std::cout << "[LOCALISATION] Langue chargee avec succes : " << lang << " (" << translations.size() << " cles)" << std::endl;
		return true;
}

string LocalisationManager::getTranslation(const string& key) const {
		auto it = translations.find(key);
		if (it != translations.end()) {
				return it->second;
		}
		return "[" + key + "]";
}
