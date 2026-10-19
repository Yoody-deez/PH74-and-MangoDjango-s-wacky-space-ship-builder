#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/resourceManager.h"
#include "../core/vector2.h"

class VisualControl : public EventObserver {
protected:
    Vector2 position;
    Vector2 size;

public:
    virtual ~VisualControl();

    virtual void render() = 0;
    virtual void setPosition(Vector2 pos);
    virtual void setSize(Vector2 s);
    
    void onEvent(Event e) override;
};