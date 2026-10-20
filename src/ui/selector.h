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

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
            float mouseY = e.mousePos.y;

            if (e.mousePos.x >= posRef.x && e.mousePos.x <= posRef.x + sizeRef.x &&
                mouseY >= posRef.y && mouseY <= posRef.y + sizeRef.y) {
                
                if (e.mousePos.x < posRef.x + (sizeRef.x / 2.0f)) {
                    if (currentIndex > 0) {
                        currentIndex--;
                    } else {
                        currentIndex = (int)options.size() - 1;
                    }
                    std::cout << "Selector: Index précédent -> " << currentIndex << std::endl;
                }
                else {
                    if (currentIndex < (int)options.size() - 1) {
                        currentIndex++;
                    } else {
                        currentIndex = 0;
                    }
                    std::cout << "Selector: Index suivant -> " << currentIndex << std::endl;
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