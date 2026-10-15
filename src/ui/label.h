#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "font.h"

using namespace std;

class Label : public VisualControl {
private:
    string text;
    Font* textFont;
    Vector2 color;

public:
    Label(const string& t, Font* f, Vector2 col);

    void setText(const string& newText);
    const string& getText() const;

    void render() override;
};