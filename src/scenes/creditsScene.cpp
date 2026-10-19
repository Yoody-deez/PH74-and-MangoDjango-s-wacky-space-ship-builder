#include "creditsScene.h"
#include <iostream>

CreditsScene::CreditsScene(Texture* bgTexture, Font* gameFont)
		: Scene("CreditsScene"),
			bg(bgTexture, true),
			titleTex(new Texture("assets/textures/text/credits.bmp")),
			textTex1(new Texture("assets/textures/text/creditText1.bmp")),
			textTex2(new Texture("assets/textures/text/creditText2.bmp")),
			textTex3(new Texture("assets/textures/text/creditText3.bmp")),
			backTex(new Texture("assets/textures/text/back.bmp")),
			
			titleLabel(titleTex, Vector2(100.0f, 480.0f), Vector2(400.0f, 70.0f)),
			creditsLine1(textTex1, Vector2(100.0f, 360.0f), Vector2(500.0f, 50.0f)),
			creditsLine2(textTex2, Vector2(100.0f, 300.0f), Vector2(500.0f, 50.0f)),
			creditsLine3(textTex3, Vector2(100.0f, 240.0f), Vector2(500.0f, 50.0f)),
			
			btnBack(backTex, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
					cout << "Action: Retour au menu principal" << endl;
					SceneManager::getInstance().switchTo("MainScene");
			})
{
		bg.setPosition(Vector2(0.0f, 0.0f));
		bg.setSize(Vector2(800.0f, 600.0f));
}

CreditsScene::~CreditsScene() {
		delete titleTex;
		delete textTex1;
		delete textTex2;
		delete textTex3;
		delete backTex;
}

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
}