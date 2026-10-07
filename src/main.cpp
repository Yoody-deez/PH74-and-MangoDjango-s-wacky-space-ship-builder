#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include "WindowFactory.h"
#include "WindowManager.h"
#include "ContextGL.h"
#include "Shader.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

constexpr int   WINDOW_WIDTH = 800;
constexpr int   WINDOW_HEIGHT = 600;

constexpr float CIRCLE_RADIUS = 40.0f;
constexpr int   NUM_SEGMENTS = 64;   
constexpr float SPEED = 250.0f;

constexpr int   NUM_BUFFERS = 3;    


GLuint loadTexture(const char* filePath) {
    SDL_Surface* surface = SDL_LoadSurface(filePath);
    if (!surface) {
        std::cerr << "Erreur de chargement d'image: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_Surface* formattedSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface); 

    if (!formattedSurface) {
        std::cerr << "Erreur lors de la conversion de la surface: " << SDL_GetError() << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_DestroySurface(formattedSurface);
    return textureID;
}

void getOrthoProjection(float left, float right, float bottom, float top, float nearP, float farP, float* outMat) {
    std::fill_n(outMat, 16, 0.0f);
    outMat[0] = 2.0f / (right - left);
    outMat[5] = 2.0f / (top - bottom);
    outMat[10] = -2.0f / (farP - nearP);
    outMat[12] = -(right + left) / (right - left);
    outMat[13] = -(top + bottom) / (top - bottom);
    outMat[14] = -(farP + nearP) / (farP - nearP);
    outMat[15] = 1.0f;
}

int WinMain(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* sdlWin = SDL_CreateWindow("Cercle Texturé Ricochet", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!sdlWin) return -1;

    if (!ContextGL::getInstance().init(sdlWin)) {
        SDL_Quit();
        return -1;
    }

    GLuint shaderProgram = Shader::createShaderProgram("vertexShader.vs", "fragmentShader.fs");
    if (shaderProgram == 0) return -1;

    std::vector<float> positions;  
    std::vector<float> texCoords;   
    std::vector<float> colors;     

    positions.push_back(0.0f); positions.push_back(0.0f);
    texCoords.push_back(0.5f); texCoords.push_back(0.5f);
    colors.push_back(1.0f);    colors.push_back(1.0f); colors.push_back(1.0f);

    for (int i = 0; i <= NUM_SEGMENTS; ++i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / NUM_SEGMENTS;
        float x = CIRCLE_RADIUS * std::cos(angle);
        float y = CIRCLE_RADIUS * std::sin(angle);

        positions.push_back(x);
        positions.push_back(y);

 
        texCoords.push_back((std::cos(angle) + 1.0f) * 0.5f);
        texCoords.push_back((std::sin(angle) + 1.0f) * 0.5f);

        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }

    int totalVertices = static_cast<int>(positions.size() / 2);

    GLuint VAO;
    GLuint VBOs[NUM_BUFFERS];

    glGenVertexArrays(1, &VAO);
    glGenBuffers(NUM_BUFFERS, VBOs);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glVertexAttrib2f(3, 0.0f, 0.0f);

    glBindVertexArray(0);

    GLuint texture = loadTexture("logo.png");

    float posX = WINDOW_WIDTH / 2.0f;
    float posY = WINDOW_HEIGHT / 2.0f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disAngle(0.0f, 2.0f * static_cast<float>(M_PI));

    float randomAngle = disAngle(gen);
    float dirX = std::cos(randomAngle);
    float dirY = std::sin(randomAngle);

    float projMatrix[16];
    getOrthoProjection(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f, projMatrix);

    glUseProgram(shaderProgram);
    GLint projLoc = glGetUniformLocation(shaderProgram, "uProjection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMatrix);

    Uint64 lastTime = SDL_GetTicks();
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
        }

        posX += dirX * SPEED * deltaTime;
        posY += dirY * SPEED * deltaTime;


        if (posX - CIRCLE_RADIUS <= 0.0f) {
            posX = CIRCLE_RADIUS;
            dirX = -dirX;
        }
        else if (posX + CIRCLE_RADIUS >= WINDOW_WIDTH) {
            posX = WINDOW_WIDTH - CIRCLE_RADIUS;
            dirX = -dirX;
        }

        if (posY - CIRCLE_RADIUS <= 0.0f) {
            posY = CIRCLE_RADIUS;
            dirY = -dirY;
        }
        else if (posY + CIRCLE_RADIUS >= WINDOW_HEIGHT) {
            posY = WINDOW_HEIGHT - CIRCLE_RADIUS;
            dirY = -dirY;
        }

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

  
        glVertexAttrib2f(3, posX, posY);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, totalVertices);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(sdlWin);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(NUM_BUFFERS, VBOs);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);

    SDL_DestroyWindow(sdlWin);
    SDL_Quit();
    return 0;
}