#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"

class checkbox : public visualControl {
private:
    bool checked;
    label checkLabel;
    unsigned int VAO, VBO;
    unsigned int bgTextureID;

    unsigned int createSolidTexture(unsigned int colorHex) {
        unsigned int texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &colorHex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texID;
    }

    void initQuad() {
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

public:
    checkbox(Vector2 pos, Vector2 s, font* f, bool initialState = false)
        : checked(initialState), 
          checkLabel(initialState ? "X" : "", f, Vector2(pos.x + 8.0f, pos.y + 4.0f)),
          VAO(0), VBO(0), bgTextureID(0) {
        position = pos;
        size = s;
        initQuad();
        bgTextureID = createSolidTexture(0xFF222222);
    }

    ~checkbox() override {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
        if (bgTextureID != 0) glDeleteTextures(1, &bgTextureID);
    }

    bool isChecked() const { return checked; }
    void setChecked(bool c) { 
        checked = c; 
        checkLabel.setText(checked ? "X" : "");
    }

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
            float correctedMouseY = 600.0f - e.mousePos.y;
            if (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                correctedMouseY >= position.y && correctedMouseY <= position.y + size.y) {
                checked = !checked;
                checkLabel.setText(checked ? "X" : "");
            }
        }
    }

    void render() override {
        GLint currentShader = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

        if (currentShader != 0) {
            glUniform2f(glGetUniformLocation(currentShader, "uPosition"), position.x, position.y);
            glUniform2f(glGetUniformLocation(currentShader, "uSize"), size.x, size.y);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bgTextureID);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        checkLabel.render();
    }
};