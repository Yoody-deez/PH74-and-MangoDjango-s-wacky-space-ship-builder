#pragma once
#include <string>
#include <iostream>
#include "settings.h"

class Engine {
private:
    bool isRunning;
    Settings settings;

    Engine() : isRunning(false) {}

    ~Engine() {
        stop();
    }

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

public:
    static Engine& getInstance() {
        static Engine instance;
        return instance;
    }

    void init(const std::string& configPath) {
        std::cout << "Initialisation du moteur..." << std::endl;
        
        settings.load(configPath);

        isRunning = true;
    }

    void run() {
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

    void stop() {
        if (isRunning) {
            std::cout << "Arrêt du moteur en cours..." << std::endl;
            isRunning = false;
        }
    }

    // Récupérer les paramètres
    Settings& getSettings() {
        return settings;
    }

    void saveSettings(const std::string& configPath) {
        settings.save(configPath);
        std::cout << "Paramètres sauvegardés dans : " << configPath << std::endl;
    }

    bool getIsRunning() const { return isRunning; }
};