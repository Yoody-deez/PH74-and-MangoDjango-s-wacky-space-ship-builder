#include "settingsScene.h"
#include <iostream>

SettingsScene::SettingsScene(Texture* bgTexture, Font* gameFont)
		: Scene("SettingsScene"),
			bg(bgTexture, true),
			
			titleLabel("PARAMETRES", gameFont, Vector2(100.0f, 460.0f)),
			btnApplyLabel("APPLIQUER", gameFont, Vector2(100.0f, 200.0f)),
			btnBackLabel("RETOUR", gameFont, Vector2(100.0f, 140.0f)),
			
			langSelector({ "FRANCAIS", "ENGLISH" },
					gameFont, Vector2(100.0f, 285.0f), Vector2(250.0f, 40.0f)),          
			
			btnApply(nullptr, Vector2(100.0f, 200.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Appliquer les paramètres (Index lang: " << langSelector.getCurrentIndex() << ")" << endl;
			}),
			btnBack(nullptr, Vector2(100.0f, 140.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Retour au menu principal" << endl;
					SceneManager::getInstance().switchTo("MainScene");
			})
{
		bg.setPosition(Vector2(0.0f, 0.0f));
		bg.setSize(Vector2(800.0f, 600.0f));
}

SettingsScene::~SettingsScene() {}

void SettingsScene::load() {
		cout << "Chargement de la scène : " << title << endl;
		eventManager.attach(&langSelector);
		eventManager.attach(&btnApply);
		eventManager.attach(&btnBack);
}

void SettingsScene::unload() {
		cout << "Déchargement de la scène : " << title << endl;
		eventManager.detach(&langSelector);
		eventManager.detach(&btnApply);
		eventManager.detach(&btnBack);
}

void SettingsScene::update(float dt) {}

void SettingsScene::render() {
		Matrix4x4 orthoMatrix = Matrix4x4::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		GLint currentShader = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
		if (currentShader != 0) {
				glUniformMatrix4fv(glGetUniformLocation(currentShader, "uProjection"), 1, GL_FALSE, orthoMatrix);
		}

		bg.render();
		titleLabel.render();
		
		langSelector.render(); 
		
		btnApply.render();
		btnApplyLabel.render();

		btnBack.render();
		btnBackLabel.render();
}