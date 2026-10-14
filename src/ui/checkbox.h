#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class checkbox : public visualControl {
private:
    bool checked;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 checkColor;

public:
    checkbox(Vector2 pos, Vector2 s, bool initialState = false, 
             Vector2 bCol = Vector2(0,0), Vector2 bgCol = Vector2(0.2f,0.2f), Vector2 cCol = Vector2(1,1))
        : checked(initialState), borderColor(bCol), bgColor(bgCol), checkColor(cCol) {
        position = pos;
        size = s;
    }

    bool isChecked() const { return checked; }

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
            if (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y) {
                checked = !checked;
            }
        }
    }

    void render() override {
    }
};