#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"

class slider : public visualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    float step;
    bool isHovered;
    bool isDragging;
    unsigned int VAO, VBO;
    unsigned int trackTextureID;
    label valueLabel;

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
    slider(float min, float max, float st, Vector2 pos, Vector2 s, font* f)
        : minVal(min), maxVal(max), currentVal(min), step(st),
          isHovered(false), isDragging(false), VAO(0), VBO(0), trackTextureID(0),
          valueLabel("", f, pos) {
        position = pos;
        size = s;
        initQuad();
        trackTextureID = createSolidTexture(0xFF333333);
        updateLabelPositionAndText();
    }

    ~slider() override {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
        if (trackTextureID != 0) glDeleteTextures(1, &trackTextureID);
    }

    float getValue() const { return currentVal; }

    void updateLabelPositionAndText() {
        float ratio = (currentVal - minVal) / (maxVal - minVal);
        float handleX = position.x + ratio * size.x;
        // Positionne le texte de la valeur au-dessus/sur le curseur qui suit la souris
        valueLabel.setPosition(Vector2(handleX - 10.0f, position.y + 5.0f));
        
        char buf[32];
        snprintf(buf, sizeof(buf), "%.1f", currentVal);
        valueLabel.setText(buf);
    }

    void onEvent(Event e) override {
        if (e.type == Event::Type::MOUSE_MOVE || e.type == Event::Type::MOUSE_CLICK) {
            float correctedMouseY = 600.0f - e.mousePos.y;

            isHovered = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                         correctedMouseY >= position.y - 10.0f && correctedMouseY <= position.y + size.y + 10.0f);

            if (isDragging && e.type == Event::Type::MOUSE_MOVE) {
                float ratio = (e.mousePos.x - position.x) / size.x;
                if (ratio < 0.0f) ratio = 0.0f;
                if (ratio > 1.0f) ratio = 1.0f;
                currentVal = minVal + ratio * (maxVal - minVal);
                updateLabelPositionAndText();
            }
        }
        if (e.type == Event::Type::MOUSE_CLICK) {
            float correctedMouseY = 600.0f - e.mousePos.y;
            bool clickedInside = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                                  correctedMouseY >= position.y - 15.0f && correctedMouseY <= position.y + size.y + 15.0f);

            if (e.button == 1 && clickedInside) {
                isDragging = true;
                float ratio = (e.mousePos.x - position.x) / size.x;
                if (ratio < 0.0f) ratio = 0.0f; if (ratio > 1.0f) ratio = 1.0f;
                currentVal = minVal + ratio * (maxVal - minVal);
                updateLabelPositionAndText();
            } else if (e.button == -1) { 
                isDragging = false;
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
        glBindTexture(GL_TEXTURE_2D, trackTextureID);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        valueLabel.render();
    }
};