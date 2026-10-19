#pragma once
#include <vector>
#include <algorithm>
#include "Event.h"

using namespace std;

class EventManager {
private:
    vector<EventObserver*> observers;

public:
    void attach(EventObserver* obs);

    void detach(EventObserver* obs);

    void notify(Event e);
};