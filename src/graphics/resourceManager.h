#pragma once
#include <string>
#include <unordered_map>
#include "resource.h"

class resourceManager {
private:
    std::unordered_map<std::string, resource*> resources;

public:
    ~resourceManager() {
        for (auto& pair : resources) {
            delete pair.second;
        }
        resources.clear();
    }

    void add(const std::string& title, resource* res) {
        if (resources.find(title) == resources.end()) {
            resources[title] = res;
        }
    }

    template<typename T>
    T get(const std::string& title) {
        auto it = resources.find(title);
        if (it != resources.end()) {
            return dynamic_cast<T>(it->second);
        }
        return nullptr;
    }

    void remove(const std::string& title) {
        auto it = resources.find(title);
        if (it != resources.end()) {
            delete it->second;
            resources.erase(it);
        }
    }
};