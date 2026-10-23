#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../ui/selector.h"
#include "../ui/checkbox.h"
#include "../ui/slider.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"
#include "../core/matrix4x4.h"

class settingsScene : public scene {
private:
    imageControl bg;
    
    label titleLabel;
    label lblLanguage;
    label lblResolution;
    label lblFullscreen;
    label lblVsync;
    label lblMouseSens;
    label lblFov;

    label btnApplyLabel;
    label btnBackLabel;
    
    selector langSelector;
    selector resSelector;
    checkbox chkFullscreen;
    checkbox chkVsync;
    slider sliderMouseSens;
    slider sliderFov;
    
    button btnApply;
    button btnBack;

public:
    settingsScene(texture* bgTexture, font* gameFont)
        : scene("SettingsScene"),
          bg(bgTexture, true),
          
          titleLabel("PARAMETRES", gameFont, Vector2(300.0f, 520.0f)),
          lblLanguage("LANGUE", gameFont, Vector2(80.0f, 430.0f)),
          lblResolution("RESOLUTION", gameFont, Vector2(80.0f, 370.0f)),
          lblFullscreen("PLEIN ECRAN", gameFont, Vector2(80.0f, 310.0f)),
          lblVsync("SYNCHRO VERTICALE", gameFont, Vector2(80.0f, 250.0f)),
          lblMouseSens("SENSIBILITE SOURIS", gameFont, Vector2(80.0f, 190.0f)),
          lblFov("CHAMP DE VISION (FOV)", gameFont, Vector2(80.0f, 130.0f)),

          btnApplyLabel("APPLIQUER", gameFont, Vector2(230.0f, 65.0f)),
          btnBackLabel("RETOUR", gameFont, Vector2(480.0f, 65.0f)),
          
          langSelector({ "FRANCAIS", "ENGLISH" }, gameFont, Vector2(550.0f, 430.0f), Vector2(200.0f, 30.0f)),
          resSelector({ "800x600", "1280x720", "1920x1080" }, gameFont, Vector2(550.0f, 370.0f), Vector2(200.0f, 30.0f)),
          
          chkFullscreen(Vector2(550.0f, 310.0f), Vector2(30.0f, 30.0f), gameFont, false),
          chkVsync(Vector2(550.0f, 250.0f), Vector2(30.0f, 30.0f), gameFont, true),
          
          sliderMouseSens(0.1f, 5.0f, 0.1f, Vector2(550.0f, 190.0f), Vector2(180.0f, 20.0f), gameFont),
          sliderFov(60.0f, 120.0f, 1.0f, Vector2(550.0f, 130.0f), Vector2(180.0f, 20.0f), gameFont),
          
          btnApply(nullptr, Vector2(200.0f, 60.0f), Vector2(160.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "--- Application des Paramètres ---" << std::endl;
              std::cout << "Langue index: " << langSelector.getCurrentIndex() << std::endl;
              std::cout << "Résolution index: " << resSelector.getCurrentIndex() << std::endl;
              std::cout << "Plein écran: " << (chkFullscreen.isChecked() ? "Oui" : "Non") << std::endl;
              std::cout << "VSync: " << (chkVsync.isChecked() ? "Oui" : "Non") << std::endl;
              std::cout << "Sensibilité souris: " << sliderMouseSens.getValue() << std::endl;
              std::cout << "FOV: " << sliderFov.getValue() << std::endl;
          }),
          btnBack(nullptr, Vector2(450.0f, 60.0f), Vector2(160.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
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
        eventManager.attach(&resSelector);
        eventManager.attach(&chkFullscreen);
        eventManager.attach(&chkVsync);
        eventManager.attach(&sliderMouseSens);
        eventManager.attach(&sliderFov);
        eventManager.attach(&btnApply);
        eventManager.attach(&btnBack);
    }

    void unload() override {
        std::cout << "Déchargement de la scène : " << title << std::endl;
        eventManager.detach(&langSelector);
        eventManager.detach(&resSelector);
        eventManager.detach(&chkFullscreen);
        eventManager.detach(&chkVsync);
        eventManager.detach(&sliderMouseSens);
        eventManager.detach(&sliderFov);
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

        lblLanguage.render();
        lblResolution.render();
        lblFullscreen.render();
        lblVsync.render();
        lblMouseSens.render();
        lblFov.render();

        langSelector.render();
        resSelector.render();
        
        chkFullscreen.render();
        chkVsync.render();
        
        sliderMouseSens.render();
        sliderFov.render();

        btnApply.render();
        btnApplyLabel.render();

        btnBack.render();
        btnBackLabel.render();
    }
};