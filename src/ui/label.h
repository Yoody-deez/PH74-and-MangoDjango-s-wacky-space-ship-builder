#pragma once
#include <string>
#include "../system/Event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "font.h"

class label : public visualControl {
private:
    std::string text;
    font* textFont;
    vector2 color;

public:
    label(const std::string& t, font* f, vector2 col) : text(t), textFont(f), color(col) {}

    void setText(const std::string& newText) { text = newText; }
    const std::string& getText() const { return text; }

    void render() override {
    }
};