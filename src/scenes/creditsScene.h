#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"

class creditsScene : public scene {
private:
    imageControl bg;

    texture* titleTex;
    texture* textTex1;
    texture* textTex2;
    texture* textTex3;
    texture* backTex;

    label titleLabel;
    label creditsLine1;
    label creditsLine2;
    label creditsLine3;
    button btnBack;

public:
    creditsScene(texture* bgTexture, font* gameFont)
        : scene("CreditsScene"),
          bg(bgTexture, true),
          titleTex(new texture("assets/textures/text/credits.bmp")),
          textTex1(new texture("assets/textures/text/creditText1.bmp")),
          textTex2(new texture("assets/textures/text/creditText2.bmp")),
          textTex3(new texture("assets/textures/text/creditText3.bmp")),
          backTex(new texture("assets/textures/text/back.bmp")),
          
          titleLabel(titleTex, Vector2(100.0f, 480.0f), Vector2(400.0f, 70.0f)),
          creditsLine1(textTex1, Vector2(100.0f, 360.0f), Vector2(500.0f, 50.0f)),
          creditsLine2(textTex2, Vector2(100.0f, 300.0f), Vector2(500.0f, 50.0f)),
          creditsLine3(textTex3, Vector2(100.0f, 240.0f), Vector2(500.0f, 50.0f)),
          
          btnBack(backTex, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              sceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));
    }

    ~creditsScene() override {
        delete titleTex;
        delete textTex1;
        delete textTex2;
        delete textTex3;
        delete backTex;
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
    }
};