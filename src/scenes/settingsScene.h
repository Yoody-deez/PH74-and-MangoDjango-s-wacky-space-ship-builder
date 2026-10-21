#pragma once
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

using namespace std;

class SettingsScene : public Scene {
private:
    ImageControl bg;
    
    Label titleLabel;
    Label btnApplyLabel;
    Label btnBackLabel;
    
    Selector langSelector;
    
    Button btnApply;
    Button btnBack;

public:
    SettingsScene(Texture* bgTexture, Font* gameFont);

    ~SettingsScene() override;

    void load();

    void unload();

    void update(float dt) override;

    void render() override;
};