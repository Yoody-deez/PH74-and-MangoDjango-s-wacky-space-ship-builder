#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"

using namespace std;

class Label : public VisualControl {
private:
    string text;
    Font* textFont;
    Texture* labelTexture;
    unsigned int VAO, VBO;

public:
    Label(Texture* tex, Vector2 pos, Vector2 s);

    Label(const string& t, Font* f, Vector2 pos) ;

    void initQuad();

    ~Label() override {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
    }

    void setText(const std::string& newText) { text = newText; }
    const std::string& getText() const { return text; }
    void setTexture(Texture* tex) { labelTexture = tex; }

    void render() override {
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
};