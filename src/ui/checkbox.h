#pragma once
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"

class Checkbox : public VisualControl {
private:
    bool checked;
    Label checkLabel;
    unsigned int VAO, VBO;
    unsigned int bgTextureID;

    unsigned int createSolidTexture(unsigned int colorHex);

    void initQuad();

public:
    Checkbox(Vector2 pos, Vector2 s, Font* f, bool initialState = false);

    ~Checkbox() override;

    bool isChecked() const;
    void setChecked(bool c);

    void onEvent(Event e) override;

    void render() override;
};