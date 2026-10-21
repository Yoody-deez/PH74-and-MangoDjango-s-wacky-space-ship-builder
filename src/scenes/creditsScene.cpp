#include "creditsScene.h"
#include <iostream>

CreditsScene::CreditsScene(Texture* bgTexture, Font* gameFont)
		: Scene("CreditsScene"),
			bg(bgTexture, true),
          
			titleLabel("CREDITS", gameFont, Vector2(100.0f, 480.0f)),
			creditsLine1("Par l'magination douteuse de ", gameFont, Vector2(100.0f, 360.0f)),
			creditsLine2("Malik Goundiam et le génis de ", gameFont, Vector2(100.0f, 300.0f)),
			creditsLine3("Yannick Chauvette", gameFont, Vector2(100.0f, 240.0f)),
			btnBackLabel("RETOUR", gameFont, Vector2(100.0f, 100.0f)), 
			
			btnBack(nullptr, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Retour au menu principal" << endl;
					SceneManager::getInstance().switchTo("MainScene");
			})
{
		bg.setPosition(Vector2(0.0f, 0.0f));
		bg.setSize(Vector2(800.0f, 600.0f));
}

CreditsScene::~CreditsScene() {}

void CreditsScene::load() {
		cout << "Chargement de la scène : " << title << endl;
		eventManager.attach(&btnBack);
}

void CreditsScene::unload() {
		cout << "Déchargement de la scène : " << title << endl;
		eventManager.detach(&btnBack);
}

void CreditsScene::update(float dt) {}

void CreditsScene::render() {
		bg.render();
		titleLabel.render();
		creditsLine1.render();
		creditsLine2.render();
		creditsLine3.render();
		btnBack.render();
		btnBackLabel.render();
}