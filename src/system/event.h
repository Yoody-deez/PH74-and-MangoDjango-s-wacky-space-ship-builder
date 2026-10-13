#pragma once
#include "../ui/vector2.h"

struct Event {
    enum class Type { MOUSE_CLICK, MOUSE_MOVE };
    Type type;
    vector2 mousePos;
    int button;
};

class EventObserver {
public:
    virtual ~EventObserver() = default;
    virtual void onEvent(Event e) = 0;
};