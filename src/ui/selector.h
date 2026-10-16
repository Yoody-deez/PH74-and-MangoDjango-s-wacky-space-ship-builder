#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../system/event.h"
#include "visualControl.h"
#include "imageControl.h"
#include "../graphics/texture.h"

class Selector : public VisualControl {
private:
    std::vector<Texture*> optionTextures;
    std::vector<ImageControl*> optionImages;
    int currentIndex;
    Vector2 posRef;
    Vector2 sizeRef;

public:
    Selector(const std::vector<std::string>& texturePaths, Vector2 pos, Vector2 s);

    ~Selector();

    int getCurrentIndex() const;

    void onEvent(Event e) override;

    void render() override;
};