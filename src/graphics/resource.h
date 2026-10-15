#pragma once
#include <string>

class Resource {
protected:
    std::string title;

public:
    Resource(const std::string& t);
    virtual ~Resource() = default;

    std::string getTitle() const;
};