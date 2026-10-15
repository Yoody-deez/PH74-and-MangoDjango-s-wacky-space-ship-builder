#include "selector.h"

Selector::Selector(const std::vector<std::string>& list, Font* font, Vector2 pos, Vector2 s)
		: items(list), currentIndex(0),
			btnPrev("<", font, pos, {30, s.y}, {0,0}, {0.5,0.5}, {0.7,0.7}, [this]() {
					if (currentIndex > 0) currentIndex--;
			}),
			btnNext(">", font, {pos.x + s.x - 30, pos.y}, {30, s.y}, {0,0}, {0.5,0.5}, {0.7,0.7}, [this]() {
					if (currentIndex < (int)items.size() - 1) currentIndex++;
			}),
			itemLabel(items.empty() ? "" : items[0], font, {1,1}) {
		position = pos;
		size = s;
}

std::string Selector::getSelected() const {
		if (items.empty()) return "";
		return items[currentIndex];
}

void Selector::onEvent(Event e) {
		btnPrev.onEvent(e);
		btnNext.onEvent(e);
		if (!items.empty()) {
				itemLabel.setText(items[currentIndex]);
		}
}

void Selector::render() {}