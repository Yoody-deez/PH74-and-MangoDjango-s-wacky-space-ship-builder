#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <iostream>

#include "WindowFactory.h"
#include "WindowManager.h"
#include "ContextGL.h"
#include "../build/shaders/shader.h"
#include "../build/shaders/shaderProgram.h"

#include "system/sceneManager.h"
#include "scenes/mainScene.h"
#include "scenes/settingsScene.h"
#include "scenes/creditsScene.h"
#include "graphics/texture.h"
#include "graphics/font.h"
#include "core/matrix4x4.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

using namespace std;

int WinMain(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* sdlWin = SDL_CreateWindow("Moteur 3D - C++ / OpenGL", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!sdlWin) {
        SDL_Quit();
        return -1;
    }

    if (!ContextGL::getInstance().init(sdlWin)) {
        SDL_DestroyWindow(sdlWin);
        SDL_Quit();
        return -1;
    }

    Shader vs("shaders/vertexShader.vs", GL_VERTEX_SHADER);
    if (!vs.compile()) {
        std::cerr << "Erreur de compilation du vertex shader !" << std::endl;
    }

    Shader fs("shaders/fragmentShader.fs", GL_FRAGMENT_SHADER);
    if (!fs.compile()) {
        std::cerr << "Erreur de compilation du fragment shader !" << std::endl;
    }

    ShaderProgram shaderProgram;
    shaderProgram.attach(&vs);
    shaderProgram.attach(&fs);

    if (!shaderProgram.link()) {
        std::cerr << "Erreur de linkage du shader program !" << std::endl;
        SDL_DestroyWindow(sdlWin);
        SDL_Quit();
        return -1;
    }

    shaderProgram.use();


    Matrix4x4 orthoProj = Matrix4x4::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);
    int projLoc = shaderProgram.getUniformLocation("uProjection");
    if (projLoc != -1) {
         glUniformMatrix4fv(projLoc, 1, GL_FALSE, orthoProj);
    }

    auto& sceneMgr = SceneManager::getInstance();
    Font* gameFont = new Font("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    Texture* bgTexture = new Texture("assets/textures/Skyboxes/skybox-space.png");

    sceneMgr.addScene("MainScene", new MainScene(bgTexture, gameFont));
    sceneMgr.addScene("SettingsScene", new SettingsScene(bgTexture, gameFont));
    sceneMgr.addScene("CreditsScene", new CreditsScene(bgTexture, gameFont));

    sceneMgr.switchTo("MainScene");

    Uint64 lastTime = SDL_GetTicks();
    bool isRunning = true;
    SDL_Event sdlEvent;

    while (isRunning) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }

            Event e;
            if (sdlEvent.type == SDL_EVENT_MOUSE_MOTION) {
                e.type = Event::Type::MOUSE_MOVE;
                e.mousePos = Vector2(sdlEvent.motion.x, sdlEvent.motion.y);
            }
            else if (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                e.type = Event::Type::MOUSE_CLICK;
                e.button = (sdlEvent.button.button == SDL_BUTTON_LEFT) ? 1 : -1;
                e.mousePos = Vector2(sdlEvent.button.x, sdlEvent.button.y);
            }
            else if (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                e.type = Event::Type::MOUSE_CLICK;
                e.button = -1;
                e.mousePos = Vector2(sdlEvent.button.x, sdlEvent.button.y);
            }

            if (sceneMgr.getCurrentScene()) {
                sceneMgr.getCurrentScene()->getEventManager().notify(e);
            }
        }

        sceneMgr.update(deltaTime);

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sceneMgr.render();

        SDL_GL_SwapWindow(sdlWin);
    }

    delete gameFont;
    delete bgTexture;

    SDL_DestroyWindow(sdlWin);
    SDL_Quit();
    return 0;
}