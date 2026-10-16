#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../ui/selector.h"

class settingsScene : public scene {
private:
    imageControl bg;
    
    texture* titleTex;
    texture* applyTex;
    texture* backTex;

    label titleLabel;
    selector langSelector;
    
    button btnApply;
    button btnBack;

public:
    settingsScene(texture* bgTexture, font* gameFont)
        : scene("SettingsScene"),
          bg(bgTexture, true),
          titleTex(new texture("assets/textures/text/settings.bmp")),
          applyTex(new texture("assets/textures/text/apply.bmp")),
          backTex(new texture("assets/textures/text/back.bmp")),
          
          titleLabel(titleTex, Vector2(100.0f, 460.0f), Vector2(300.0f, 60.0f)),
          langSelector({
              "assets/textures/text/langFR.bmp",    
              "assets/textures/text/langEN.bmp"    
          }, Vector2(100.0f, 285.0f), Vector2(250.0f, 40.0f)),         
          
          btnApply(applyTex, Vector2(100.0f, 200.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Appliquer les paramètres (Index lang: " << langSelector.getCurrentIndex() << ")" << std::endl;
          }),
          btnBack(backTex, Vector2(100.0f, 140.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              sceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));
    }

    ~settingsScene() override {
        delete titleTex;
        delete applyTex;
        delete backTex;
    }

    void load() override {
        std::cout << "Chargement de la scène : " << title << std::endl;
        eventManager.attach(&langSelector);
        eventManager.attach(&btnApply);
        eventManager.attach(&btnBack);
    }

    void unload() override {
        std::cout << "Déchargement de la scène : " << title << std::endl;
        eventManager.detach(&langSelector);
        eventManager.detach(&btnApply);
        eventManager.detach(&btnBack);
    }

    void update(float dt) override {}

    void render() override {
        bg.render();
        titleLabel.render();
        
        langSelector.render(); 
        
        btnApply.render();
        btnBack.render();
    }
};