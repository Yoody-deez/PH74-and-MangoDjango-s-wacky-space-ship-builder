#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"
#include "../graphics/font.h"

class selector : public visualControl {
private:
    std::vector<std::string> options;
    int currentIndex;
    Vector2 posRef;
    Vector2 sizeRef;
    label optionLabel;

public:
    selector(const std::vector<std::string>& optionTexts, font* f, Vector2 pos, Vector2 s)
        : options(optionTexts), currentIndex(0), posRef(pos), sizeRef(s),
          optionLabel(optionTexts.empty() ? "" : optionTexts[0], f, pos)
    {
        position = pos;
        size = s;
    }

    ~selector() {}

    int getCurrentIndex() const {
        return currentIndex;
    }

    void setCurrentIndex(int index) {
        if (!options.empty()) {
            currentIndex = (index >= 0 && index < (int)options.size()) ? index : 0;
            optionLabel.setText(options[currentIndex]);
        }
    }

    void setItems(const std::vector<std::string>& newItems) {
        options = newItems;
        if (!options.empty()) {
            if (currentIndex >= (int)options.size()) {
                currentIndex = 0;
            }
            optionLabel.setText(options[currentIndex]);
        }
    }  

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
            float correctedMouseY = 600.0f - e.mousePos.y;

            if (e.mousePos.x >= posRef.x && e.mousePos.x <= posRef.x + sizeRef.x &&
                correctedMouseY >= posRef.y && correctedMouseY <= posRef.y + sizeRef.y) {
                
                if (e.mousePos.x < posRef.x + (sizeRef.x / 2.0f)) {
                    currentIndex = (currentIndex > 0) ? currentIndex - 1 : (int)options.size() - 1;
                } else {
                    currentIndex = (currentIndex < (int)options.size() - 1) ? currentIndex + 1 : 0;
                }

                if (!options.empty()) {
                    optionLabel.setText(options[currentIndex]);
                }
            }
        }
    }

    void render() override {
        if (!options.empty()) {
            optionLabel.render();
        }
    }
};