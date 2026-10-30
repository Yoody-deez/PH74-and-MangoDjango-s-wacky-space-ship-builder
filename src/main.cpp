#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <iostream>
#include <filesystem>

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
#include "core/configManager.h"
#include "settings/settingsApplier.h"
#include "settings/localisationManager.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int WinMain(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::filesystem::path configPath = std::filesystem::path(__FILE__).parent_path() / "settings" / "settings.xml";

    if (ConfigManager::getInstance().loadFromFile(configPath.string())) {
        std::cout << "[CONFIG] Parametres charges depuis le fichier :" << std::endl;
    } else {
        std::cout << "[CONFIG] Utilisation des valeurs par defaut." << std::endl;
    }

    std::cout << "  - Langue Index : " << ConfigManager::getInstance().getLanguageIndex() << std::endl;
    std::cout << "  - Resolution Index : " << ConfigManager::getInstance().getResolutionIndex() << std::endl;
    std::cout << "  - Plein ecran : " << (ConfigManager::getInstance().isFullscreen() ? "Oui" : "Non") << std::endl;
    std::cout << "  - VSync : " << (ConfigManager::getInstance().isVsync() ? "Oui" : "Non") << std::endl;
    std::cout << "  - Sensibilite Souris : " << ConfigManager::getInstance().getMouseSensitivity() << std::endl;
    std::cout << "  - FOV : " << ConfigManager::getInstance().getFov() << std::endl;

    int langIdx = ConfigManager::getInstance().getLanguageIndex();
    std::string langCode = (langIdx == 1) ? "en" : "fr";
    LocalisationManager::getInstance().setLanguage(langCode);

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

    SettingsApplier::applySettings(sdlWin);

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


    Matrix4x4 orthoProj = Matrix4x4::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);        int projLoc = shaderProgram.getUniformLocation("uProjection");
    if (projLoc != -1) {
         glUniformMatrix4fv(projLoc, 1, GL_FALSE, orthoProj);
    }

    auto& sceneMgr = SceneManager::getInstance();
    Font* gameFont = new Font("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    Texture* bgTexture = new Texture("assets/textures/Skyboxes/skybox-space.png");

    sceneMgr.addScene("MainScene", new MainScene(bgTexture, gameFont));
    sceneMgr.addScene("SettingsScene", new SettingsScene(bgTexture, gameFont, sdlWin));
    sceneMgr.addScene("CreditsScene", new CreditsScene(bgTexture, gameFont));
    sceneMgr.switchTo("MainScene");

    Uint64 lastTime = SDL_GetTicks();
    bool isRunning = true;
    SDL_Event sdlEvent;

    while (isRunning) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        int winWidth, winHeight;
        SDL_GetWindowSize(sdlWin, &winWidth, &winHeight);
        float scaleX = 800.0f / (float)winWidth;
        float scaleY = 600.0f / (float)winHeight;

        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }

            Event e;
            if (sdlEvent.type == SDL_EVENT_MOUSE_MOTION) {
                e.type = Event::Type::MOUSE_MOVE;
                e.mousePos = Vector2(sdlEvent.motion.x * scaleX, sdlEvent.motion.y * scaleY);
            }
            else if (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                e.type = Event::Type::MOUSE_CLICK;
                e.button = (sdlEvent.button.button == SDL_BUTTON_LEFT) ? 1 : -1;
                e.mousePos = Vector2(sdlEvent.button.x * scaleX, sdlEvent.button.y * scaleY);
            }
            else if (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                e.type = Event::Type::MOUSE_CLICK;
                e.button = -1;
                e.mousePos = Vector2(sdlEvent.button.x * scaleX, sdlEvent.button.y * scaleY);
            }

            if (sceneMgr.getCurrentScene()) {
                sceneMgr.getCurrentScene()->getEventManager().notify(e);
            }
        }

        Matrix4x4 orthoProj = Matrix4x4::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        int projLoc = shaderProgram.getUniformLocation("uProjection");
        if (projLoc != -1) {
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, orthoProj);
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