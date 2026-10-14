#include "resource.h"


resource::resource(const std::string& t) : title(t) {}
resource::~resource() = default;

std::string resource::getTitle() const { return title; }