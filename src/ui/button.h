#pragma once
#include <string>
#include <functional>
#include "../system/Event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "label.h"
#include "font.h"

class button : public visualControl {
private:
    label titleLabel;
    vector2 borderColor;
    vector2 bgColor;
    vector2 hoverColor;
    bool isHovered;
    std::function<void()> onClick;

public:
    button(const std::string& title, font* font, vector2 pos, vector2 s, 
           vector2 bCol, vector2 bgCol, vector2 hCol, std::function<void()> callback)
        : titleLabel(title, font, {1.0f, 1.0f}), borderColor(bCol), 
          bgColor(bgCol), hoverColor(hCol), isHovered(false), onClick(callback) {
        position = pos;
        size = s;
    }

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_MOVE) {
            isHovered = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                         e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y);
        }
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1 && isHovered) {
            if (onClick) onClick();
        }
    }

    void render() override {
    }
};