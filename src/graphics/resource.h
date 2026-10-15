#pragma once
#include <string>

using namespace std;

class Resource {
protected:
    string title;

public:
    Resource(const string& t);
    virtual ~Resource() = default;

    string getTitle() const;
};