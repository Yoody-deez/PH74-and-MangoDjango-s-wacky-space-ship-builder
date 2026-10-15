#include "checkbox.h"

Checkbox::Checkbox(bool initialState, Vector2 bCol, Vector2 bgCol, Vector2 cCol)
		: checked(initialState), borderColor(bCol), bgColor(bgCol), checkColor(cCol) {}

bool Checkbox::isChecked() const { return checked; }

void Checkbox::onEvent(Event e) {
		if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
				if (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
						e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y) {
						checked = !checked;
				}
		}
}

void Checkbox::render() {}