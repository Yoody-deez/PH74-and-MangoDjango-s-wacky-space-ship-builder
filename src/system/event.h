#pragma once
#include "vector2.h"

struct Event {
    enum class Type { MOUSE_CLICK, MOUSE_MOVE };
    Type type;
    Vector2 mousePos;
    int button;
};

class EventObserver {
public:
    virtual ~EventObserver() = default;
    virtual void onEvent(Event e) = 0;
};