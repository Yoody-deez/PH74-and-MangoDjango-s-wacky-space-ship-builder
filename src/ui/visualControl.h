#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/resourceManager.h"
#include "vector2.h"

class visualControl : public EventObserver {
protected:
    vector2 position;
    vector2 size;

public:
    virtual ~visualControl() = default;

    virtual void render() = 0;
    virtual void setPosition(vector2 pos) { position = pos; }
    virtual void setSize(vector2 s) { size = s; }
    
    void onEvent(Event e) override {}
};