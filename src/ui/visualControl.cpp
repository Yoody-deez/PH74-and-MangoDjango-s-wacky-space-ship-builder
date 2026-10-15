#include "visualControl.h"

VisualControl::~VisualControl() = default;

void VisualControl::setPosition(Vector2 pos) { position = pos; }
void VisualControl::setSize(Vector2 s) { size = s; }

void VisualControl::onEvent(Event e) {}
