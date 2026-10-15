#include "button.h"

Button::Button(const std::string& title, Font* font, Vector2 pos, Vector2 s, 
				Vector2 bCol, Vector2 bgCol, Vector2 hCol, std::function<void()> callback)
		: titleLabel(title, font, {1.0f, 1.0f}), borderColor(bCol), 
			bgColor(bgCol), hoverColor(hCol), isHovered(false), onClick(callback) {
		position = pos;
		size = s;
}

void Button::onEvent(Event e) {
		if (e.type == Event::Type::MOUSE_MOVE) {
				isHovered = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
											e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y);
		}
		if (e.type == Event::Type::MOUSE_CLICK && e.button == 1 && isHovered) {
				if (onClick) onClick();
		}
}

void Button::render() {}