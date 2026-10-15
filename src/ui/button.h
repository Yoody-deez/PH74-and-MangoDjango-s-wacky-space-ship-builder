#pragma once
#include <string>
#include <functional>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "label.h"
#include "font.h"

using namespace std;

class Button : public VisualControl {
private:
    Label titleLabel;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 hoverColor;
    bool isHovered;
    function<void()> onClick;

public:
    Button(const string& title, Font* font, Vector2 pos, Vector2 s, 
           Vector2 bCol, Vector2 bgCol, Vector2 hCol, function<void()> callback);

    void onEvent(Event e) override;

    void render() override;
};