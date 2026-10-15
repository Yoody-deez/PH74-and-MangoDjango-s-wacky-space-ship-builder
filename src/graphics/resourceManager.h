#pragma once
#include <string>
#include <unordered_map>
#include "resource.h"

using namespace std;

class ResourceManager {
private:
    unordered_map<string, Resource*> resources;

public:
    ~ResourceManager();

    void add(const string& title, Resource* res);

    template<typename T>
    T get(const string& title);

    void remove(const string& title);
};