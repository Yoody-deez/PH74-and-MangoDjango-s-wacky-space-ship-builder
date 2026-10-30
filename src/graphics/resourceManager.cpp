#include "resourceManager.h"

ResourceManager::~ResourceManager() {
		for (auto& pair : resources) {
				delete pair.second;
		}
		resources.clear();
}

void ResourceManager::add(const std::string& title, Resource* res) {
		if (resources.find(title) == resources.end()) {
				resources[title] = res;
		}
}

template<typename T>
T ResourceManager::get(const std::string& title) {
		auto it = resources.find(title);
		if (it != resources.end()) {
				return dynamic_cast<T>(it->second);
		}
		return nullptr;
}

void ResourceManager::remove(const std::string& title) {
		auto it = resources.find(title);
		if (it != resources.end()) {
				delete it->second;
				resources.erase(it);
		}
}