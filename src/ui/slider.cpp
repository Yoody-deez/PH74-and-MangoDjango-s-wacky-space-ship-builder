#include "slider.h"

    Slider::Slider(float min, float max, float st, Vector2 bCol, Vector2 bgCol, Vector2 pCol)
        : minVal(min), maxVal(max), currentVal(min), step(st), 
          borderColor(bCol), bgColor(bgCol), progressColor(pCol), 
          isHovered(false), isDragging(false) {}

    float Slider::getValue() const { return currentVal; }

    void Slider::onEvent(Event e) {
        if (e.type == Event::Type::MOUSE_MOVE) {
            isHovered = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                         e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y);
            if (isDragging) {
                float ratio = (e.mousePos.x - position.x) / size.x;
                if (ratio < 0.0f) ratio = 0.0f;
                if (ratio > 1.0f) ratio = 1.0f;
                currentVal = minVal + ratio * (maxVal - minVal);
            }
        }
        if (e.type == Event::Type::MOUSE_CLICK) {
            if (e.button == 1) {
                if (isHovered) isDragging = true;
            } else if (e.button == -1) { 
                isDragging = false;
            }
        }
    }

    void Slider::render() {}