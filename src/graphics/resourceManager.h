#pragma once
#include <string>
#include <unordered_map>
#include "resource.h"

class ResourceManager {
private:
    std::unordered_map<std::string, Resource*> resources;

public:
    ~ResourceManager();

    void add(const std::string& title, Resource* res);

    template<typename T>
    T get(const std::string& title);

    void remove(const std::string& title);
};