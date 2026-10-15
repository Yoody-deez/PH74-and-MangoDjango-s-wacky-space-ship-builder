#include "Resource.h"


Resource::Resource(const string& t) : title(t) {}
Resource::~Resource() = default;

string Resource::getTitle() const { return title; }