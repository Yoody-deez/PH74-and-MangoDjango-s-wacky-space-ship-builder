#include "Resource.h"


Resource::Resource(const string& t) : title(t) {}

string Resource::getTitle() const { return title; }