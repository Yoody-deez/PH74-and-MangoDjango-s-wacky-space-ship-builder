#pragma once
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"

using namespace std;

class CreditsScene : public Scene {
private:
    ImageControl bg;

    Texture* backTex;

    Label titleLabel;
    Label creditsLine1;
    Label creditsLine2;
    Label creditsLine3;
    Button btnBack;
    Label btnBackLabel;

public:
    CreditsScene(Texture* bgTexture, Font* gameFont)
        : Scene("CreditsScene"),
          bg(bgTexture, true),
          
          titleLabel("CREDITS", gameFont, Vector2(100.0f, 480.0f)),
          creditsLine1("Par l'magination douteuse de ", gameFont, Vector2(100.0f, 360.0f)),
          creditsLine2("Malik Goundiam et le génis de ", gameFont, Vector2(100.0f, 300.0f)),
          creditsLine3("Yannick Chauvette", gameFont, Vector2(100.0f, 240.0f)),
          btnBackLabel("RETOUR", gameFont, Vector2(100.0f, 100.0f)), 
          
          btnBack(nullptr, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
              std::cout << "Action: Retour au menu principal" << std::endl;
              SceneManager::getInstance().switchTo("MainScene");
          })
    {
        bg.setPosition(Vector2(0.0f, 0.0f));
        bg.setSize(Vector2(800.0f, 600.0f));
    }

    ~CreditsScene() override {
    }

    void load() override;

    void unload() override;

    void update(float dt) override;

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