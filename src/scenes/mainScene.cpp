#include "mainScene.h"
#include <iostream>

MainScene::MainScene(Texture* bgTexture, Font* gameFont) 
		: Scene("MainScene"),
			bg(bgTexture, true),
			titleTex(new Texture("assets/textures/text/titre.bmp")),
			playTex(new Texture("assets/textures/text/play.bmp")),
			settingsTex(new Texture("assets/textures/text/settings.bmp")),
			creditsTex(new Texture("assets/textures/text/credits.bmp")),
			quitTex(new Texture("assets/textures/text/quit.bmp")),
			
			titleLabel(titleTex, Vector2(100.0f, 450.0f), Vector2(600.0f, 60.0f)),
			
			btnStart(playTex, Vector2(100.0f, 300.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
					cout << "Action: Démarrer le jeu" << endl;
					// Exemple : sceneManager::getInstance().switchTo("GameScene");
			}),
			btnSettings(settingsTex, Vector2(100.0f, 240.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
					cout << "Action: Ouvrir les paramètres" << endl;
					SceneManager::getInstance().switchTo("SettingsScene");
			}),
			btnCredits(creditsTex, Vector2(100.0f, 180.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
					cout << "Action: Afficher les crédits" << endl;
					SceneManager::getInstance().switchTo("CreditsScene");
			}),
			btnQuit(quitTex, Vector2(100.0f, 120.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
					cout << "Action: Quitter l'application" << endl;
					Engine::getInstance().stop();
					SDL_Event quitEvent;
					quitEvent.type = SDL_EVENT_QUIT;
					SDL_PushEvent(&quitEvent);
			})
{
		bg.setPosition({0.0f, 0.0f});
		bg.setSize({800.0f, 600.0f});
}

MainScene::~MainScene() {
		delete titleTex;
		delete playTex;
		delete settingsTex;
		delete creditsTex;
		delete quitTex;
}

void MainScene::load() {
		cout << "Chargement de la scène : " << title << endl;
		eventManager.attach(&btnStart);
		eventManager.attach(&btnSettings);
		eventManager.attach(&btnCredits);
		eventManager.attach(&btnQuit);
}

void MainScene::unload() {
		cout << "Déchargement de la scène : " << title << endl;
		eventManager.detach(&btnStart);
		eventManager.detach(&btnSettings);
		eventManager.detach(&btnCredits);
		eventManager.detach(&btnQuit);
}

void MainScene::update(float dt) {}

void MainScene::render() {
		Matrix4x4 orthoMatrix = Matrix4x4::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		GLint currentShader = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
		if (currentShader != 0) {
				glUniformMatrix4fv(glGetUniformLocation(currentShader, "uProjection"), 1, GL_FALSE, orthoMatrix);
		}

		bg.render();
		titleLabel.render();
		btnStart.render();
		btnSettings.render();
		btnCredits.render();
		btnQuit.render();
}