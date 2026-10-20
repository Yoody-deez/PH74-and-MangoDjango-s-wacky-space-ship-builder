#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"

class creditsScene : public scene {
private:
    imageControl bg;

    texture* backTex;

    label titleLabel;
    label creditsLine1;
    label creditsLine2;
    label creditsLine3;
    button btnBack;
    label btnBackLabel;

public:
    creditsScene(texture* bgTexture, font* gameFont)
        : scene("CreditsScene"),
          bg(bgTexture, true),
          
          titleLabel("CREDITS", gameFont, Vector2(100.0f, 480.0f)),
          creditsLine1("Par l'magination douteuse de ", gameFont, Vector2(100.0f, 360.0f)),
          creditsLine2("Malik Goundiam et le génis de ", gameFont, Vector2(100.0f, 300.0f)),
          creditsLine3("Yannick Chauvette", gameFont, Vector2(100.0f, 240.0f)),
          btnBackLabel("RETOUR", gameFont, Vector2(100.0f, 100.0f)), 
          
          btnBack(nullptr, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              sceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));
    }

    ~creditsScene() override {
    }

    void load() override {
        std::cout << "Chargement de la scène : " << title << std::endl;
        eventManager.attach(&btnBack);
    }

    void unload() override {
        std::cout << "Déchargement de la scène : " << title << std::endl;
        eventManager.detach(&btnBack);
    }

    void update(float dt) override {}

    void render() override {
        bg.render();
        titleLabel.render();
        creditsLine1.render();
        creditsLine2.render();
        creditsLine3.render();
        btnBack.render();
        btnBackLabel.render();
    }
};