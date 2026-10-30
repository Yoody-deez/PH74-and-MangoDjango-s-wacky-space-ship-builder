#include "selector.h"
#include <iostream>


    Selector::Selector(const std::vector<std::string>& optionTexts, Font* f, Vector2 pos, Vector2 s)
        : options(optionTexts), currentIndex(0), posRef(pos), sizeRef(s),
          optionLabel(optionTexts.empty() ? "" : optionTexts[0], f, pos)
    {
        position = pos;
        size = s;
    }

    Selector::~Selector() {}

    int Selector::getCurrentIndex() const {
        return currentIndex;
    }

    void Selector::setCurrentIndex(int index) {
        if (!options.empty()) {
            currentIndex = (index >= 0 && index < (int)options.size()) ? index : 0;
            optionLabel.setText(options[currentIndex]);
        }
    }

    void Selector::setItems(const std::vector<std::string>& newItems) {
        options = newItems;
        if (!options.empty()) {
            if (currentIndex >= (int)options.size()) {
                currentIndex = 0;
            }
            optionLabel.setText(options[currentIndex]);
        }
    }  

    void Selector::onEvent(Event e) {
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

    void Selector::render() {
        if (!options.empty()) {
            optionLabel.render();
        }
    }
