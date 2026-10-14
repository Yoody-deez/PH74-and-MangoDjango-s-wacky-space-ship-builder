#pragma once
#include <vector>
#include <algorithm>
#include "Event.h"

class EventManager {
private:
    std::vector<EventObserver*> observers;

public:
    void attach(EventObserver* obs) {
        if (obs && std::find(observers.begin(), observers.end(), obs) == observers.end()) {
            observers.push_back(obs);
        }
    }

    void detach(EventObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
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