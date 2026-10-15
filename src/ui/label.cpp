#include "label.h"


Label::Label(const std::string& t, Font* f, Vector2 col) : text(t), textFont(f), color(col) {}

void Label::setText(const std::string& newText) { text = newText; }
const std::string& Label::getText() const { return text; }

void Label::render() {}