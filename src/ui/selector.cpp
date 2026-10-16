#include "selector.h"
#include <iostream>

Selector::Selector(const std::vector<std::string>& texturePaths, Vector2 pos, Vector2 s)
		: currentIndex(0), posRef(pos), sizeRef(s) {
		position = pos;
		size = s;

		for (const auto& path : texturePaths) {
				Texture* tex = new Texture(path.c_str());
				optionTextures.push_back(tex);
				
				ImageControl* img = new ImageControl(tex, true);
				img->setPosition(pos);
				img->setSize(s);
				optionImages.push_back(img);
		}
}

Selector::~Selector() {
		for (auto img : optionImages) {
				delete img;
		}
		for (auto tex : optionTextures) {
				delete tex;
		}
		optionImages.clear();
		optionTextures.clear();
}

int Selector::getCurrentIndex() const {
		return currentIndex;
}

void Selector::onEvent(Event e) {
		if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
				
				float mouseY = e.mousePos.y;

				std::cout << "Clic Souris -> X: " << e.mousePos.x << " | Y: " << mouseY << std::endl;
						std::cout << "Attendu Selector -> X: [" << posRef.x << " ; " << (posRef.x + sizeRef.x) 
											<< "] | Y: [" << posRef.y << " ; " << (posRef.y + sizeRef.y) << "]" << std::endl;

				if (e.mousePos.x >= posRef.x && e.mousePos.x <= posRef.x + sizeRef.x &&
						mouseY >= posRef.y && mouseY <= posRef.y + sizeRef.y) {
						
						if (e.mousePos.x < posRef.x + (sizeRef.x / 2.0f)) {
								if (currentIndex > 0) {
										currentIndex--;
								} else {
										currentIndex = (int)optionImages.size() - 1;
								}
								std::cout << "Selector: Index précédent -> " << currentIndex << std::endl;
						}
						else {
								if (currentIndex < (int)optionImages.size() - 1) {
										currentIndex++;
								} else {
										currentIndex = 0;
								}
								std::cout << "Selector: Index suivant -> " << currentIndex << std::endl;
						}
				}
		}
}

void Selector::render() {
		if (!optionImages.empty() && optionImages[currentIndex]) {
				optionImages[currentIndex]->render();
		}
}