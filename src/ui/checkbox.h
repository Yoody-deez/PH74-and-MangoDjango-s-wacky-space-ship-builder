#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class Checkbox : public VisualControl {
private:
    bool checked;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 checkColor;
    unsigned int VAO, VBO;

    void initQuad();

public:
    Checkbox(Vector2 pos, Vector2 s, bool initialState = false, 
             Vector2 bCol = Vector2(0,0), Vector2 bgCol = Vector2(0.2f,0.2f), Vector2 cCol = Vector2(1,1));

    ~Checkbox() override;

    bool isChecked() const;
    void setChecked(bool c);

    void onEvent(Event e) override;

    void render() override;
};