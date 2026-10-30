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
#include "../settings/localisationManager.h"

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
    MainScene(Texture* bgTexture, Font* gameFont);

    ~MainScene() override;

    void updateTexts();

    void load() override;

    void unload() override;

    void update(float dt) override;

    void render() override;
};