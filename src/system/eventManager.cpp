#pragma once
#include "eventManager.h"
#include <algorithm>

void EventManager::attach(EventObserver* obs) {
		if (obs && std::find(observers.begin(), observers.end(), obs) == observers.end()) {
				observers.push_back(obs);
		}
}

void EventManager::detach(EventObserver* obs) {
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void EventManager::notify(Event e) {
		auto observersCopy = observers;
		for (auto* obs : observersCopy) {
				if (obs) {
						obs->onEvent(e);
				}
		}
}
