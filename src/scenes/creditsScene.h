#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"

class creditsScene : public scene {
private:
    label titleLabel;
    label creditsTextLabel;
    button btnBack;

public:
    creditsScene(font* gameFont)
        : scene("CreditsScene"),
          titleLabel("Crédits", gameFont, Vector2(1.0f, 1.0f)),
          creditsTextLabel("Développé avec amour\nEngine 3D C++ / OpenGL", gameFont, Vector2(1.0f, 1.0f)),
          btnBack("Retour", gameFont, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              // Plus tard : sceneManager::getInstance().switchTo("MainScene");
          })
    {
        titleLabel.setPosition(Vector2(100.0f, 480.0f));
        titleLabel.setSize(Vector2(300.0f, 60.0f));

        creditsTextLabel.setPosition(Vector2(100.0f, 300.0f));
        creditsTextLabel.setSize(Vector2(400.0f, 120.0f));
    }

    void load() override {
        std::cout << "Chargement de la scène : " << title << std::endl;

        eventManager.attach(&btnBack);
    }

    void unload() override {
        std::cout << "Déchargement de la scène : " << title << std::endl;

        eventManager.detach(&btnBack);
    }

    void update(float dt) override {
    
    }

    void render() override {
        titleLabel.render();
        creditsTextLabel.render();
        btnBack.render();
    }
};