#include "selector.h"
#include <iostream>

Selector::Selector(const vector<string>& optionTexts, Font* f, Vector2 pos, Vector2 s)
		: options(optionTexts), currentIndex(0), posRef(pos), sizeRef(s),
			optionLabel(optionTexts.empty() ? "" : optionTexts[0], f, pos)
{
		position = pos;
		size = s;
}

Selector::~Selector() {}

int Selector::getCurrentIndex() const {
		return currentIndex;
}

void Selector::onEvent(Event e) {
		if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
				float mouseY = e.mousePos.y;

				if (e.mousePos.x >= posRef.x && e.mousePos.x <= posRef.x + sizeRef.x &&
						mouseY >= posRef.y && mouseY <= posRef.y + sizeRef.y) {
						
						if (e.mousePos.x < posRef.x + (sizeRef.x / 2.0f)) {
								if (currentIndex > 0) {
										currentIndex--;
								} else {
										currentIndex = (int)options.size() - 1;
								}
								cout << "Selector: Index précédent -> " << currentIndex << endl;
						}
						else {
								if (currentIndex < (int)options.size() - 1) {
										currentIndex++;
								} else {
										currentIndex = 0;
								}
								cout << "Selector: Index suivant -> " << currentIndex << endl;
						}

						if (!options.empty()) {
								optionLabel.setText(options[currentIndex]);
						}
				}
		}
}

void Selector::render() {
		if (!options.empty()) {
				optionLabel.render();
		}
}