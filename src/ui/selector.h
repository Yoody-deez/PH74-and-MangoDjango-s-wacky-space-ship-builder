#pragma once
#include <string>
#include <vector>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"
#include "button.h"
#include "label.h"
#include "font.h"

class selector : public visualControl {
private:
    std::vector<std::string> items;
    int currentIndex;
    button btnPrev;
    button btnNext;
    label itemLabel;

public:
    selector(const std::vector<std::string>& list, font* font, Vector2 pos, Vector2 s)
        : items(list), currentIndex(0),
          btnPrev("<", font, pos, {30, s.y}, {0,0}, {0.5,0.5}, {0.7,0.7}, [this]() {
              if (currentIndex > 0) currentIndex--;
          }),
          btnNext(">", font, {pos.x + s.x - 30, pos.y}, {30, s.y}, {0,0}, {0.5,0.5}, {0.7,0.7}, [this]() {
              if (currentIndex < (int)items.size() - 1) currentIndex++;
          }),
          itemLabel(items.empty() ? "" : items[0], font, {1,1}) {
        position = pos;
        size = s;
    }

    std::string getSelected() const {
        if (items.empty()) return "";
        return items[currentIndex];
    }

    void onEvent(Event e) override {
        btnPrev.onEvent(e);
        btnNext.onEvent(e);
        if (!items.empty()) {
            itemLabel.setText(items[currentIndex]);
        }
    }

    void render() override {
        btnPrev.render();
        btnNext.render();
        itemLabel.render();
    }
};