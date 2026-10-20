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
#include "../ui/selector.h"
#include "../core/matrix4x4.h"

class settingsScene : public scene {
private:
    imageControl bg;
    
    label titleLabel;
    label btnApplyLabel;
    label btnBackLabel;
    
    selector langSelector;
    
    button btnApply;
    button btnBack;

public:
    settingsScene(texture* bgTexture, font* gameFont)
        : scene("SettingsScene"),
          bg(bgTexture, true),
          
          titleLabel("PARAMETRES", gameFont, Vector2(100.0f, 460.0f)),
          btnApplyLabel("APPLIQUER", gameFont, Vector2(100.0f, 200.0f)),
          btnBackLabel("RETOUR", gameFont, Vector2(100.0f, 140.0f)),
          
          langSelector({ "FRANCAIS", "ENGLISH" },
             gameFont, Vector2(100.0f, 285.0f), Vector2(250.0f, 40.0f)),          
          
          btnApply(nullptr, Vector2(100.0f, 200.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Appliquer les paramètres (Index lang: " << langSelector.getCurrentIndex() << ")" << std::endl;
          }),
          btnBack(nullptr, Vector2(100.0f, 140.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              sceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));
    }

    ~settingsScene() override {}

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
        matrix4x4 orthoMatrix = matrix4x4::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

        GLint currentShader = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
        if (currentShader != 0) {
            glUniformMatrix4fv(glGetUniformLocation(currentShader, "uProjection"), 1, GL_FALSE, orthoMatrix);
        }

        bg.render();
        titleLabel.render();
        
        langSelector.render(); 
        
        btnApply.render();
        btnApplyLabel.render();

        btnBack.render();
        btnBackLabel.render();
    }
};