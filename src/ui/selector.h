#pragma once
#include <string>
#include <vector>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "button.h"
#include "label.h"
#include "font.h"

using namespace std;

class Selector : public VisualControl {
private:
    vector<string> items;
    int currentIndex;
    Button btnPrev;
    Button btnNext;
    Label itemLabel;

public:
    Selector(const vector<string>& list, Font* font, Vector2 pos, Vector2 s);

    string getSelected() const;

    void onEvent(Event e) override;

    void render() override;
};