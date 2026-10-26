#include "label.h"
//TODO: Gérer les codes caractères UTF-8 pour prendre en charge les accents, ligne 87

Label::Label(Texture* tex, Vector2 pos, Vector2 s) 
		: text(""), textFont(nullptr), labelTexture(tex), VAO(0), VBO(0) {
		position = pos;
		size = s;
		initQuad();
}

Label::Label(const string& t, Font* f, Vector2 pos) 
		: text(t), textFont(f), labelTexture(nullptr), VAO(0), VBO(0) {
		position = pos;
		size = Vector2(100.0f, 30.0f);
		initQuad();
}

Label::Label(const string& id, Font* f, Vector2 pos, bool localized) 
		: text(""), textID(id), textFont(f), labelTexture(nullptr), VAO(0), VBO(0), isLocalized(localized) {
		position = pos;
		isLocalized = localized;
		size = Vector2(100.0f, 30.0f);
		initQuad();
		if (isLocalized && !textID.empty()) {
				updateLocalizedText();
		}
}

void Label::initQuad() {
		float vertices[] = {
				0.0f, 1.0f,  0.0f, 1.0f,  
				0.0f, 0.0f,  0.0f, 0.0f,  
				1.0f, 0.0f,  1.0f, 0.0f,  

				0.0f, 1.0f,  0.0f, 1.0f,  
				1.0f, 0.0f,  1.0f, 0.0f,  
				1.0f, 1.0f,  1.0f, 1.0f   
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
}

Label::~Label() {
		if (VAO != 0) glDeleteVertexArrays(1, &VAO);
		if (VBO != 0) glDeleteBuffers(1, &VBO);
}

void Label::setText(const string& newText) { 
		text = newText;
		codepoints = DecodeUTF8(text); // Décodage du texte UTF-8 en points de code Unicode
		/*
				À noter: la plage actelle U+0020 à U+00FF ne couvre pas tous les caractères utilisés dans la langue française, donc certains caractères accentués peuvent ne pas s'afficher correctement. Il faudra peut-être étendre la plage de caractères supportée pour les inclure.
				Exploration possible avec stbtt_PackFontRanges() pour inlcure uniquement les caractères qu'on veut utiliser.
		*/
}
const string& Label::getText() const { return text; }

void Label::setTextID(const string& id)
{
    textID = id;
		if (isLocalized && !textID.empty()) {
				updateLocalizedText();
		}
}

void Label::updateLocalizedText()
{
    if (!textID.empty())
    {
        //setText(LocalisationManager::getInstance().getTranslation(textID));
    }
}

void Label::setTexture(Texture* tex) { labelTexture = tex; }

void Label::render() {
		GLint currentShader = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (labelTexture) {
				if (currentShader != 0) {
						glUniform2f(glGetUniformLocation(currentShader, "uPosition"), position.x, position.y);
						glUniform2f(glGetUniformLocation(currentShader, "uSize"), size.x, size.y);
				}
				glActiveTexture(GL_TEXTURE0);
				labelTexture->bind();
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				labelTexture->unbind();
		} 
		else if (textFont && textFont->isLoaded() && !text.empty()) {
				if (currentShader != 0) {
						glUniform2f(glGetUniformLocation(currentShader, "uPosition"), 0.0f, 0.0f);
						glUniform2f(glGetUniformLocation(currentShader, "uSize"), 1.0f, 1.0f);
				}

				textFont->bindAtlas();
				glBindVertexArray(VAO);

				float x = position.x;
				float y = position.y + size.y;  

				for (char c : text) {
						if (c >= 32 && c < 128) {
								stbtt_aligned_quad q;
								stbtt_GetBakedQuad(textFont->getBakedChars(), 512, 512, c - 32, &x, &y, &q, 1);

								float vertices[] = {
										q.x0, q.y1,  q.s0, q.t0,  
										q.x0, q.y0,  q.s0, q.t1,    
										q.x1, q.y0,  q.s1, q.t1,  

										q.x0, q.y1,  q.s0, q.t0,
										q.x1, q.y0,  q.s1, q.t1,
										q.x1, q.y1,  q.s1, q.t0    
								};

								glBindBuffer(GL_ARRAY_BUFFER, VBO);
								glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

								glDrawArrays(GL_TRIANGLES, 0, 6);
						}
				}

				glBindVertexArray(0);
				textFont->unbindAtlas();
		}
}