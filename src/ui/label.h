#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"

class Label : public VisualControl {
private:
    string text;
    Font* textFont;
    Texture* labelTexture;
    unsigned int VAO, VBO;

public:
    Label(Texture* tex, Vector2 pos, Vector2 s);

    Label(const std::string& t, Font* f, Vector2 pos) ;

    void initQuad();

    ~Label();

    void setText(const string& newText);
    const std::string& getText() const;
    void setTexture(Texture* tex);

    void render() override;
};