#include <fstream>
#include <sstream>
#include <iostream>
#include "settings.h"

bool Settings::load(const string& filePath) {
		ifstream file(filePath);
		if (!file.is_open()) {
				cerr << "AVERTISSEMENT::SETTINGS::FICHIER_INTROUVABLE : " << filePath << " (Création par défaut)" << endl;
				return false;
		}

		string line;
		while (getline(file, line)) {
				if (line.empty() || line[0] == '#') continue;

				stringstream ss(line);
				string key, value;
				if (getline(ss, key, '=') && getline(ss, value)) {
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

bool Settings::save(const string& filePath) {
		ofstream file(filePath);
		if (!file.is_open()) {
				cerr << "ERREUR::SETTINGS::IMPOSSIBLE_D_ECRIRE : " << filePath << endl;
				return false;
		}

		for (const auto& pair : data) {
				file << pair.first << "=" << pair.second << "\n";
		}
		file.close();
		return true;
}

string Settings::get(const string& key, const string& defaultValue) const {
		auto it = data.find(key);
		if (it != data.end()) {
				return it->second;
		}
		return defaultValue;
}

// Définir une valeur
void Settings::set(const string& key, const string& value) {
		data[key] = value;
}