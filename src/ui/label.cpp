#include "label.h"


Label::Label(const std::string& t, Font* f, Vector2 col) : text(t), textFont(f), color(col) {}

void Label::setText(const std::string& newText) { text = newText; }
const std::string& Label::getText() const { return text; }

void Label::render() {
	/* Note de Yannick: Proposition de Copilot. À vérifier et à compléter. Le code ci-dessous est un exemple générique.
		// Render the label using the text, font, and color
		// This is a placeholder implementation; actual rendering code will depend on the graphics library being used.
		if (textFont) {
				textFont->renderText(text, position, color);
		}*/
}