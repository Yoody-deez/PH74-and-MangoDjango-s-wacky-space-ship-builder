#pragma once
#include <vector>
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"
#include "../graphics/font.h"

class Selector : public VisualControl {
private:
    std::vector<std::string> options;
    int currentIndex;
    Vector2 posRef;
    Vector2 sizeRef;
    Label optionLabel;

public:
    Selector(const std::vector<std::string>& optionTexts, Font* f, Vector2 pos, Vector2 s);

    ~Selector();

    int getCurrentIndex() const;

    void setCurrentIndex(int index);

    void setItems(const std::vector<std::string>& newItems);

    void onEvent(Event e) override;

    void render() override;
};