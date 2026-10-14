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
    checkbox(bool initialState, Vector2 bCol, Vector2 bgCol, Vector2 cCol)
        : checked(initialState), borderColor(bCol), bgColor(bgCol), checkColor(cCol) {}

    bool isChecked() const {}

    void onEvent(Event e) override {}

    void render() override {}
};