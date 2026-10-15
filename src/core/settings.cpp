#include <fstream>
#include <sstream>
#include <iostream>
#include "settings.h"

bool Settings::load(const std::string& filePath) {
		std::ifstream file(filePath);
		if (!file.is_open()) {
				std::cerr << "AVERTISSEMENT::SETTINGS::FICHIER_INTROUVABLE : " << filePath << " (Création par défaut)" << std::endl;
				return false;
		}

		std::string line;
		while (std::getline(file, line)) {
				if (line.empty() || line[0] == '#') continue;

				std::stringstream ss(line);
				std::string key, value;
				if (std::getline(ss, key, '=') && std::getline(ss, value)) {
						key.erase(0, key.find_first_not_of(" \t"));
						key.erase(key.find_last_not_of(" \t") + 1);
						value.erase(0, value.find_first_not_of(" \t"));
						value.erase(value.find_last_not_of(" \t") + 1);

						data[key] = value;
				}
		}
		file.close();
		return true;
}

bool Settings::save(const std::string& filePath) {
		std::ofstream file(filePath);
		if (!file.is_open()) {
				std::cerr << "ERREUR::SETTINGS::IMPOSSIBLE_D_ECRIRE : " << filePath << std::endl;
				return false;
		}

		for (const auto& pair : data) {
				file << pair.first << "=" << pair.second << "\n";
		}
		file.close();
		return true;
}

std::string Settings::get(const std::string& key, const std::string& defaultValue) const {
		auto it = data.find(key);
		if (it != data.end()) {
				return it->second;
		}
		return defaultValue;
}

// Définir une valeur
void Settings::set(const std::string& key, const std::string& value) {
		data[key] = value;
}