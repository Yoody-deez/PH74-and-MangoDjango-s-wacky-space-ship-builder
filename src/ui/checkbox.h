#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class Checkbox : public VisualControl {
private:
    bool checked;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 checkColor;

public:
    Checkbox(bool initialState, Vector2 bCol, Vector2 bgCol, Vector2 cCol);

    bool isChecked() const;

    void onEvent(Event e) override;

    void render() override;
};