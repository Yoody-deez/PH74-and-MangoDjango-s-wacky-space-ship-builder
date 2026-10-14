#include "label.h"


label::label(const std::string& t, font* f, Vector2 col) : text(t), textFont(f), color(col) {}

void label::setText(const std::string& newText) { text = newText; }
const std::string& label::getText() const { return text; }

void label::render() {
}