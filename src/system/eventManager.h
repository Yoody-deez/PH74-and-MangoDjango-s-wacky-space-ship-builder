#pragma once
#include <vector>
#include <algorithm>
#include "Event.h"

using namespace std;

class EventManager {
private:
    vector<EventObserver*> observers;

public:
    void attach(EventObserver* obs) {
        if (obs && find(observers.begin(), observers.end(), obs) == observers.end()) {
            observers.push_back(obs);
        }
    }

    void detach(EventObserver* obs) {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify(Event e) {
        auto observersCopy = observers;
        for (auto* obs : observersCopy) {
            if (obs) {
                obs->onEvent(e);
            }
        }
    }
};