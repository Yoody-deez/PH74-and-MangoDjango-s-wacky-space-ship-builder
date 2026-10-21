#pragma once
#include <vector>
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"
#include "../graphics/font.h"

using namespace std;

class Selector : public VisualControl {
private:
    vector<string> options;
    int currentIndex;
    Vector2 posRef;
    Vector2 sizeRef;
    Label optionLabel;

public:
    Selector(const vector<string>& optionTexts, Font* f, Vector2 pos, Vector2 s);

    ~Selector();

    int getCurrentIndex() const;

    void onEvent(Event e) override;

    void render() override;
};