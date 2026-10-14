#include "resourceManager.h"

resourceManager::~resourceManager() {
		for (auto& pair : resources) {
				delete pair.second;
		}
		resources.clear();
}

void resourceManager::add(const std::string& title, resource* res) {
		if (resources.find(title) == resources.end()) {
				resources[title] = res;
		}
}

template<typename T>
T resourceManager::get(const std::string& title) {
		auto it = resources.find(title);
		if (it != resources.end()) {
				return dynamic_cast<T>(it->second);
		}
		return nullptr;
}

void resourceManager::remove(const std::string& title) {
		auto it = resources.find(title);
		if (it != resources.end()) {
				delete it->second;
				resources.erase(it);
		}
}