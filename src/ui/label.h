#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "font.h"

class Label : public VisualControl {
private:
    std::string text;
    Font* textFont;
    Vector2 color;

public:
    Label(const std::string& t, Font* f, Vector2 col);

    void setText(const std::string& newText);
    const std::string& getText() const;

    void render() override;
};