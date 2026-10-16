#pragma once
#include "../system/scene.h"
#include "../system/sceneManager.h"
#include "../ui/imageControl.h"
#include "../ui/label.h"
#include "../ui/button.h"
#include "../core/engine.h"
#include "../graphics/texture.h"
#include "../core/matrix4x4.h"

using namespace std;

class MainScene : public Scene {
private:
    ImageControl bg;
    
    Texture* titleTex;
    Texture* playTex;
    Texture* settingsTex;
    Texture* creditsTex;
    Texture* quitTex;

    Label titleLabel;
    
    Button btnStart;
    Button btnSettings;
    Button btnCredits;
    Button btnQuit;

public:
    MainScene(Texture* bgTexture, Font* gameFont);

    ~MainScene() override;

    void load() override;

    void unload() override;

    void update(float dt) override;

    void render() override;
};