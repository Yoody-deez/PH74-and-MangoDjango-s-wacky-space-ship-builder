#pragma once
#include <SDL3/SDL.h>
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
#include "../core/configManager.h"
#include "../settings/localisationManager.h"
#include "../settings/settingsApplier.h"

class SettingsScene : public Scene {
private:
    ImageControl bg;
    
    Label titleLabel;
    Label lblLanguage;
    Label lblResolution;
    Label lblFullscreen;
    Label lblVsync;
    Label lblMouseSens;
    Label lblFov;

    Label btnApplyLabel;
    Label btnBackLabel;
    
    Selector langSelector;
    Selector resSelector;
    Checkbox chkFullscreen;
    Checkbox chkVsync;
    Slider sliderMouseSens;
    Slider sliderFov;
    
    Button btnApply;
    Button btnBack;

    SDL_Window* m_sdlWin;

public:
    SettingsScene(Texture* bgTexture, Font* gameFont, SDL_Window* sdlWin);

    ~SettingsScene() override;

    void updateTexts();

    void load() override;

    void unload() override;

    void update(float dt) override;

    void render() override;
};