#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/font.h"
#include "../graphics/texture.h"

class label : public visualControl {
private:
    std::string text;
    font* textFont;
    unsigned int VAO, VBO;

public:
    label(const std::string& t, font* f, Vector2 pos) 
        : text(t), textFont(f), VAO(0), VBO(0) {
        
        position = pos; 

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

    ~label() override {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
    }

    void setText(const std::string& newText) { text = newText; }
    const std::string& getText() const { return text; }

    void render() override {
        if (!textFont || !textFont->getAtlas() || text.empty()) return;

        GLint currentShader = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

        float cursorX = position.x;
        float cursorY = position.y;
        
        float charWidth = 12.0f;  
        float charHeight = 20.0f; 

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Corrigé ici

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
};