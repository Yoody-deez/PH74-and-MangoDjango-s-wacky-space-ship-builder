#pragma once
#include <string>
#include <functional>
#include <glad/gl.h>
#include "../system/event.h"
#include "../graphics/texture.h"
#include "visualControl.h"
#include "label.h"

using namespace std;

class Button : public VisualControl {
private:
    Label titleLabel;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 hoverColor;
    bool isHovered;
    function<void()> onClick;
    unsigned int VAO, VBO;
    unsigned int buttonTextureID;

    unsigned int createSolidTexture(unsigned int colorHex);

public:
    Button(Texture* btnTex, Vector2 pos, Vector2 s, 
           Vector2 bCol, Vector2 bgCol, Vector2 hCol, std::function<void()> callback);

    ~Button() override;

    void onEvent(Event e) override;

    void render() override;
};