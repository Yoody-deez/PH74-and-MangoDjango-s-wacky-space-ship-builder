#include "eventManager.h"

void EventManager::attach(EventObserver* obs) {
		if (obs && find(observers.begin(), observers.end(), obs) == observers.end()) {
				observers.push_back(obs);
		}
}

void EventManager::detach(EventObserver* obs) {
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}

void EventManager::notify(Event e) {
		auto observersCopy = observers;
		for (auto* obs : observersCopy) {
				if (obs) {
						obs->onEvent(e);
				}
		}
}