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
    CreditsScene(Texture* bgTexture, Font* gameFont);

    ~CreditsScene() override ;

    void load() override;

    void unload() override;

    void update(float dt) override;

    void render() override;
};