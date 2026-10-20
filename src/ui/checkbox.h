#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class checkbox : public visualControl {
private:
    bool checked;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 checkColor;
    unsigned int VAO, VBO;

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
    checkbox(Vector2 pos, Vector2 s, bool initialState = false, 
             Vector2 bCol = Vector2(0,0), Vector2 bgCol = Vector2(0.2f,0.2f), Vector2 cCol = Vector2(1,1))
        : checked(initialState), borderColor(bCol), bgColor(bgCol), checkColor(cCol), VAO(0), VBO(0) {
        position = pos;
        size = s;
        initQuad();
    }

    ~checkbox() override {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
    }

    bool isChecked() const { return checked; }
    void setChecked(bool c) { checked = c; }

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1) {
            if (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                e.mousePos.y >= position.y && e.mousePos.y <= position.y + size.y) {
                checked = !checked;
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

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};