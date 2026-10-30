#include "button.h"
#include <glad/gl.h>


    unsigned int Button::createSolidTexture(unsigned int colorHex) {
        unsigned int texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &colorHex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texID;
    }

    Button::Button(Texture* btnTex, Vector2 pos, Vector2 s, 
           Vector2 bCol, Vector2 bgCol, Vector2 hCol, std::function<void()> callback)
        : titleLabel(btnTex, pos, s), borderColor(bCol), 
          bgColor(bgCol), hoverColor(hCol), isHovered(false), onClick(callback), VAO(0), VBO(0), buttonTextureID(0) {
        position = pos;
        size = s;
        titleLabel.setPosition(pos);
        titleLabel.setSize(s);

        buttonTextureID = createSolidTexture(0xFF111111);

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

    Button::~Button() {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
        if (buttonTextureID != 0) glDeleteTextures(1, &buttonTextureID);
    }

    void Button::onEvent(Event e) {
        if (e.type == Event::Type::MOUSE_MOVE || e.type == Event::Type::MOUSE_CLICK) {
            float correctedMouseY = 600.0f - e.mousePos.y;

            isHovered = (e.mousePos.x >= position.x && e.mousePos.x <= position.x + size.x &&
                         correctedMouseY >= position.y && correctedMouseY <= position.y + size.y);
        }
        
        if (e.type == Event::Type::MOUSE_CLICK && e.button == 1 && isHovered) {
            if (onClick) onClick();
        }
    }

    void Button::render() {
        GLint currentShader = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

        if (currentShader != 0) {
            glUniform2f(glGetUniformLocation(currentShader, "uPosition"), position.x, position.y);
            glUniform2f(glGetUniformLocation(currentShader, "uSize"), size.x, size.y);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, buttonTextureID);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        titleLabel.render();
    }
