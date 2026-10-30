#include "configManager.h"
#include <fstream>
#include <sstream>
#include <iostream>


ConfigManager::ConfigManager() 
		: languageIndex(0), resolutionIndex(0), fullscreen(false), 
			vsync(true), mouseSensitivity(1.0f), fov(90.0f) {}

std::string ConfigManager::extractTagValue(const std::string& line, const std::string& tag) {
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

ConfigManager& ConfigManager::getInstance() {
		static ConfigManager instance;
		return instance;
}

bool ConfigManager::loadFromFile(const std::string& filepath) {
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

void ConfigManager::saveToFile(const std::string& filepath) {
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

int ConfigManager::getLanguageIndex() const { return languageIndex; }
void ConfigManager::setLanguageIndex(int val) { languageIndex = val; }

int ConfigManager::getResolutionIndex() const { return resolutionIndex; }
void ConfigManager::setResolutionIndex(int val) { resolutionIndex = val; }

bool ConfigManager::isFullscreen() const { return fullscreen; }
void ConfigManager::setFullscreen(bool val) { fullscreen = val; }

bool ConfigManager::isVsync() const { return vsync; }
void ConfigManager::setVsync(bool val) { vsync = val; }

float ConfigManager::getMouseSensitivity() const { return mouseSensitivity; }
void ConfigManager::setMouseSensitivity(float val) { mouseSensitivity = val; }

float ConfigManager::getFov() const { return fov; }
void ConfigManager::setFov(float val) { fov = val; }