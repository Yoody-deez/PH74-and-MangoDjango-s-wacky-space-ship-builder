#pragma once
#include <vector>
#include "Event.h"

class EventManager {
private:
    std::vector<EventObserver*> observers;

public:
    void attach(EventObserver* obs);

    void detach(EventObserver* obs);

    void notify(Event e);
};