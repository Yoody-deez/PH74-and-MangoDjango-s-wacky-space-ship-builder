#pragma once
#include <string>

class resource {
protected:
    std::string title;

public:
    resource(const std::string& t) : title(t) {}
    virtual ~resource() = default;

    std::string getTitle() const { return title; }
};