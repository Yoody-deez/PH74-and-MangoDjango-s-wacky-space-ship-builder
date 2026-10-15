#include "label.h"


Label::Label(const string& t, Font* f, Vector2 col) : text(t), textFont(f), color(col) {}

void Label::setText(const string& newText) { text = newText; }
const string& Label::getText() const { return text; }

void Label::render() {}