#include "label.h"


Label::Label(Texture* tex, Vector2 pos, Vector2 s) 
		: text(""), textFont(nullptr), labelTexture(tex), VAO(0), VBO(0) {
		position = pos;
		size = s;
		initQuad();
}

Label::Label(const std::string& t, Font* f, Vector2 pos) 
		: text(t), textFont(f), labelTexture(nullptr), VAO(0), VBO(0) {
		position = pos;
		size = Vector2(100.0f, 30.0f);
		initQuad();
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

void Label::setText(const string& newText) { text = newText; }
const string& Label::getText() const { return text; }
void Label::setTexture(Texture* tex) { labelTexture = tex; }

void Label::render() {
		GLint currentShader = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

		if (currentShader != 0) {
				glUniform2f(glGetUniformLocation(currentShader, "uPosition"), position.x, position.y);
				glUniform2f(glGetUniformLocation(currentShader, "uSize"), size.x, size.y);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (labelTexture) {
				glActiveTexture(GL_TEXTURE0);
				labelTexture->bind();

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);

				labelTexture->unbind();
		} 
		else if (textFont && textFont->getAtlas() && !text.empty()) {
				float cursorX = position.x;
				float cursorY = position.y;
				float charWidth = 12.0f;  
				float charHeight = 20.0f; 

				glActiveTexture(GL_TEXTURE0);
				textFont->getAtlas()->bind();
				glBindVertexArray(VAO);

				for (char c : text) {
						unsigned char ascii = (unsigned char)c;
						int col = ascii % 16;
						int row = ascii / 16;

						float u0 = (float)col / 16.0f;
						float u1 = (float)(col + 1) / 16.0f;
						float v_top = 1.0f - (float)row / 16.0f;
						float v_bottom = 1.0f - (float)(row + 1) / 16.0f;

						float vertices[] = {
								0.0f, 1.0f,  u0, v_bottom, 
								0.0f, 0.0f,  u0, v_top,    
								1.0f, 0.0f,  u1, v_top,

								0.0f, 1.0f,  u0, v_bottom,
								1.0f, 0.0f,  u1, v_top,
								1.0f, 1.0f,  u1, v_bottom
						};

						glBindBuffer(GL_ARRAY_BUFFER, VBO);
						glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

						if (currentShader != 0) {
								glUniform2f(glGetUniformLocation(currentShader, "uPosition"), cursorX, cursorY);
								glUniform2f(glGetUniformLocation(currentShader, "uSize"), charWidth, charHeight);
						}

						glDrawArrays(GL_TRIANGLES, 0, 6);
						cursorX += charWidth * 0.85f; 
				}
				glBindVertexArray(0);
				textFont->getAtlas()->unbind();
		}
}