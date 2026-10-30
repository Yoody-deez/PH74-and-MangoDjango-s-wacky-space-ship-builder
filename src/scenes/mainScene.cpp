#include "mainScene.h"
#include <iostream>
#include <SDL3/SDL.h>

MainScene::MainScene(Texture* bgTexture, Font* gameFont) 
		: Scene("MainScene"),
		bg(bgTexture, true),
		titleLabel(LocalisationManager::getInstance().getTranslation("Main_Title"), gameFont, Vector2(100.0f, 450.0f)),
		btnStartLabel(LocalisationManager::getInstance().getTranslation("Main_PlayButton"), gameFont, Vector2(100.0f, 300.0f)),
		btnSettingsLabel(LocalisationManager::getInstance().getTranslation("Main_SettingsButton"), gameFont, Vector2(100.0f, 240.0f)),
		btnCreditsLabel(LocalisationManager::getInstance().getTranslation("Main_CreditsButton"), gameFont, Vector2(100.0f, 180.0f)),
		btnQuitLabel(LocalisationManager::getInstance().getTranslation("Main_QuitButton"), gameFont, Vector2(100.0f, 120.0f)),

		btnStart(nullptr, Vector2(100.0f, 300.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
				std::cout << "Action: Démarrer le jeu" << std::endl;
		}),
		btnSettings(nullptr, Vector2(100.0f, 240.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
				std::cout << "Action: Ouvrir les paramètres" << std::endl;
				SceneManager::getInstance().switchTo("SettingsScene");
		}),
		btnCredits(nullptr, Vector2(100.0f, 180.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
				std::cout << "Action: Afficher les crédits" << std::endl;
				SceneManager::getInstance().switchTo("CreditsScene");
		}),
		btnQuit(nullptr, Vector2(100.0f, 120.0f), Vector2(200.0f, 50.0f), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f), Vector2(0.4f, 0.4f), [this]() {
				std::cout << "Action: Quitter l'application" << std::endl;
				Engine::getInstance().stop();
				SDL_Event quitEvent;
				quitEvent.type = SDL_EVENT_QUIT;
				SDL_PushEvent(&quitEvent);
		})
{
		bg.setPosition({0.0f, 0.0f});
		bg.setSize({800.0f, 600.0f});
}

MainScene::~MainScene() {}

void MainScene::updateTexts() {
		titleLabel.setText(LocalisationManager::getInstance().getTranslation("Main_Title"));
		btnStartLabel.setText(LocalisationManager::getInstance().getTranslation("Main_PlayButton"));
		btnSettingsLabel.setText(LocalisationManager::getInstance().getTranslation("Main_SettingsButton"));
		btnCreditsLabel.setText(LocalisationManager::getInstance().getTranslation("Main_CreditsButton"));
		btnQuitLabel.setText(LocalisationManager::getInstance().getTranslation("Main_QuitButton"));
}

void MainScene::load() {
		std::cout << "Chargement de la scène : " << title << std::endl;
		updateTexts();
		eventManager.attach(&btnStart);
		eventManager.attach(&btnSettings);
		eventManager.attach(&btnCredits);
		eventManager.attach(&btnQuit);
}

void MainScene::unload() {
		std::cout << "Déchargement de la scène : " << title << std::endl;
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
		btnStartLabel.render(); 

		btnSettings.render();
		btnSettingsLabel.render();

		btnCredits.render();
		btnCreditsLabel.render();

		btnQuit.render();
		btnQuitLabel.render();
}