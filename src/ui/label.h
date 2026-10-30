#pragma once
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"
#include "../ui/utf8.h"

class Label : public VisualControl {
private:
    std::string text;
    Font* textFont;
    Texture* labelTexture;
    unsigned int VAO;
    unsigned int VBO;

public:
    Label(Texture* tex, Vector2 pos, Vector2 s);

    Label(const std::string& t, Font* f, Vector2 pos);

    void initQuad();

    ~Label() override;

    void setText(const std::string& newText);
    const std::string& getText() const;
    void setTexture(Texture* tex);

    void render() override;
};