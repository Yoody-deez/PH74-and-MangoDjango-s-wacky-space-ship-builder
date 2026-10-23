#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"

using namespace std;

class Label : public VisualControl {
private:
    string text;
    string textID;
    Font* textFont;
    Texture* labelTexture;
    unsigned int VAO, VBO;

public:
    Label(Texture* tex, Vector2 pos, Vector2 s);
    Label(const string& t, Font* f, Vector2 pos);
    Label(const string& id, Font* f, Vector2 pos, 
        bool localized);

    void initQuad();

    ~Label();

    void setText(const string& newText);
    const string& getText() const;
    void setTextID(const string& id);
    void updateLocalizedText();

    void setTexture(Texture* tex);

    void render() override;
};