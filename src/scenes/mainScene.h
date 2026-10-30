#pragma once
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"
#include "../core/matrix4x4.h"

class MainScene : public Scene {
private:
    ImageControl bg;
    
    Label titleLabel;
    Label btnStartLabel;
    Label btnSettingsLabel;
    Label btnCreditsLabel;
    Label btnQuitLabel;

    Button btnStart;
    Button btnSettings;
    Button btnCredits;
    Button btnQuit;

public:
    MainScene(Texture* bgTexture, Font* gameFont) 
        : Scene("MainScene"),
          bg(bgTexture, true),
          titleLabel("Wacky Space SHip Builder", gameFont, Vector2(100.0f, 450.0f)),
          btnStartLabel("JOUER", gameFont, Vector2(100.0f, 300.0f)),
          btnSettingsLabel("PARAMETRES", gameFont, Vector2(100.0f, 240.0f)),
          btnCreditsLabel("CREDITS", gameFont, Vector2(100.0f, 180.0f)),
          btnQuitLabel("QUITTER", gameFont, Vector2(100.0f, 120.0f)),

          btnStart(nullptr, Vector2(100.0f, 300.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
              std::cout << "Action: Démarrer le jeu" << std::endl;
          }),
          btnSettings(nullptr, Vector2(100.0f, 240.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
              std::cout << "Action: Ouvrir les paramètres" << std::endl;
              SceneManager::getInstance().switchTo("SettingsScene");
          }),
          btnCredits(nullptr, Vector2(100.0f, 180.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
              std::cout << "Action: Afficher les crédits" << std::endl;
              SceneManager::getInstance().switchTo("CreditsScene");
          }),
          btnQuit(nullptr, Vector2(100.0f, 120.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
              std::cout << "Action: Quitter l'application" << std::endl;
              Engine::getInstance().stop();
              SDL_Event quitEvent;
              quitEvent.type = SDL_EVENT_QUIT;
              SDL_PushEvent(&quitEvent);
          })
    {
        bg.setPosition({0.0f, 0.0f});
        bg.setSize({800.0f, 600.0f});
    }

    ~MainScene() override {}

    void load() override;

    void unload() override;

    void update(float dt) override;

    void render() override {
        Matrix4x4 orthoMatrix = Matrix4x4::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

        GLint currentShader = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
        if (currentShader != 0) {
            glUniformMatrix4fv(glGetUniformLocation(currentShader, "uProjection"), 1, GL_FALSE, orthoMatrix);
        }

        bg.render();
        titleLabel.render();
        
        btnStart.render();
        btnStartLabel.render(); 

        btnSettings.render();
        btnSettingsLabel.render();

        btnCredits.render();
        btnCreditsLabel.render();

        btnQuit.render();
        btnQuitLabel.render();
    }
};