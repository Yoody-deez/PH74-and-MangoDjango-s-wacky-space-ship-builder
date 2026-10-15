#include "Resource.h"


Resource::Resource(const std::string& t) : title(t) {}
Resource::~Resource() = default;

std::string Resource::getTitle() const { return title; }