#include "settingsScene.h"
#include <iostream>

SettingsScene::SettingsScene(Texture* bgTexture, Font* gameFont)
		: Scene("SettingsScene"),
			bg(bgTexture, true),
			titleTex(new Texture("assets/textures/text/settings.bmp")),
			applyTex(new Texture("assets/textures/text/apply.bmp")),
			backTex(new Texture("assets/textures/text/back.bmp")),
			
			titleLabel(titleTex, Vector2(100.0f, 460.0f), Vector2(300.0f, 60.0f)),
			langSelector({
					"assets/textures/text/langFR.bmp",    
					"assets/textures/text/langEN.bmp"    
			}, Vector2(100.0f, 285.0f), Vector2(250.0f, 40.0f)),         
			
			btnApply(applyTex, Vector2(100.0f, 200.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Appliquer les paramètres (Index lang: " << langSelector.getCurrentIndex() << ")" << endl;
			}),
			btnBack(backTex, Vector2(100.0f, 140.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Retour au menu principal" << endl;
					SceneManager::getInstance().switchTo("MainScene");
			})
{
		bg.setPosition(Vector2(0.0f, 0.0f));
		bg.setSize(Vector2(800.0f, 600.0f));
}

SettingsScene::~SettingsScene() {
		delete titleTex;
		delete applyTex;
		delete backTex;
}

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
		bg.render();
		titleLabel.render();
		
		langSelector.render(); 
		
		btnApply.render();
		btnBack.render();
}