#pragma once
#include <string>
#include <vector>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "button.h"
#include "label.h"
#include "font.h"

class Selector : public VisualControl {
private:
    std::vector<std::string> items;
    int currentIndex;
    Button btnPrev;
    Button btnNext;
    Label itemLabel;

public:
    Selector(const std::vector<std::string>& list, Font* font, Vector2 pos, Vector2 s);

    std::string getSelected() const;

    void onEvent(Event e) override;

    void render() override;
};