#include <iostream>
#include "settings.h"
#include "engine.h"

Engine::Engine() : isRunning(false) {}

Engine::~Engine() {
		stop();
}

Engine::Engine(const Engine&) = delete;
Engine& Engine::operator=(const Engine&) = delete;

Engine& Engine::getInstance() {
		static Engine instance;
		return instance;
}

void Engine::init(const std::string& configPath) {
		std::cout << "Initialisation du moteur..." << std::endl;
		
		settings.load(configPath);

		isRunning = true;
}

void Engine::run() {
		std::cout << "Démarrage de la boucle principale (Engine::run)..." << std::endl;
		
		while (isRunning) {
				// 1. Gérer les entrées clavier/souris (Poll events)
				// 2. Mettre à jour la logique du jeu / de l'UI
				// 3. Rendu graphique (OpenGL)
				
				// Pour l'instant, on s'assure qu'on peut sortir de la boucle si besoin
				// (Tu ajouteras la condition de fermeture de fenêtre ici plus tard)
				break;
		}
}

void Engine::stop() {
		if (isRunning) {
				std::cout << "Arrêt du moteur en cours..." << std::endl;
				isRunning = false;
		}
}

// Récupérer les paramètres
Settings& Engine::getSettings() {
		return settings;
}

void Engine::saveSettings(const std::string& configPath) {
		settings.save(configPath);
		std::cout << "Paramètres sauvegardés dans : " << configPath << std::endl;
}

bool Engine::getIsRunning() const { return isRunning; }