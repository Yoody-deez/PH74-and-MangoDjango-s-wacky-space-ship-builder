#pragma once
#include <iostream>
#include "../system/scene.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../ui/selector.h"
#include "../ui/checkbox.h"
#include "../ui/slider.h"
#include "../core/engine.h"

class settingsScene : public scene {
private:
    imageControl bg;
    label titleLabel;
    
    // Composants des paramètres
    selector langSelector;
    selector resSelector;
    checkbox fullscreenCb;
    checkbox vsyncCb;
    slider sensitivitySlider;
    slider fovSlider;
    
    button btnApply;
    button btnBack;

public:
    settingsScene(texture* bgTexture, font* gameFont)
        : scene("SettingsScene"),
          bg(bgTexture, true),
          titleLabel("Paramètres", gameFont, Vector2(1.0f, 1.0f)),
          
          langSelector({"Français", "English"}, gameFont, Vector2(100.0f, 380.0f), Vector2(250.0f, 40.0f)),
          resSelector({"1280x720", "1920x1080", "2560x1440"}, gameFont, Vector2(100.0f, 320.0f), Vector2(250.0f, 40.0f)),
          
          fullscreenCb(Vector2(100.0f, 260.0f), Vector2(30.0f, 30.0f)),
          vsyncCb(Vector2(100.0f, 210.0f), Vector2(30.0f, 30.0f)),
          
          sensitivitySlider(0.1f, 1.0f, 5.0f, Vector2(100.0f, 160.0f), Vector2(200.0f, 20.0f)),
          fovSlider(60.0f, 90.0f, 120.0f, Vector2(100.0f, 110.0f), Vector2(200.0f, 20.0f)),
          
          btnApply("Appliquer", gameFont, Vector2(100.0f, 40.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Appliquer les paramètres" << std::endl;
          }),
          btnBack("Retour", gameFont, Vector2(260.0f, 40.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              // Plus tard : SceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));

        titleLabel.setPosition(Vector2(100.0f, 460.0f));
        titleLabel.setSize(Vector2(300.0f, 60.0f));
    }

    ~settingsScene() override = default;

    void load() override {
        std::cout << "Chargement de la scène : " << title << std::endl;

        eventManager.attach(&langSelector);
        eventManager.attach(&resSelector);
        eventManager.attach(&fullscreenCb);
        eventManager.attach(&vsyncCb);
        eventManager.attach(&sensitivitySlider);
        eventManager.attach(&fovSlider);
        eventManager.attach(&btnApply);
        eventManager.attach(&btnBack);
    }

    void unload() override {
        std::cout << "Déchargement de la scène : " << title << std::endl;

        eventManager.detach(&langSelector);
        eventManager.detach(&resSelector);
        eventManager.detach(&fullscreenCb);
        eventManager.detach(&vsyncCb);
        eventManager.detach(&sensitivitySlider);
        eventManager.detach(&fovSlider);
        eventManager.detach(&btnApply);
        eventManager.detach(&btnBack);
    }

    void update(float dt) override {
    
    }

    void render() override {
        bg.render();
        titleLabel.render();
        
        langSelector.render();
        resSelector.render();
        fullscreenCb.render();
        vsyncCb.render();
        sensitivitySlider.render();
        fovSlider.render();
        
        btnApply.render();
        btnBack.render();
    }
};