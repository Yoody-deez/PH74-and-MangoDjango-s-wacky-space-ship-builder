#include "resource.h"
    Resource::Resource(const std::string& t) : title(t) {}

    std::string Resource::getTitle() const { return title; }