#pragma once
#include <string>
#include "../system/Event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class checkbox : public visualControl {
private:
    bool checked;
    vector2 borderColor;
    vector2 bgColor;
    vector2 checkColor;

public:
    checkbox(bool initialState, vector2 bCol, vector2 bgCol, vector2 cCol)
        : checked(initialState), borderColor(bCol), bgColor(bgCol), checkColor(cCol) {}

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