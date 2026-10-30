#include "creditsScene.h"
#include <iostream>


CreditsScene::CreditsScene(Texture* bgTexture, Font* gameFont)
		: Scene("CreditsScene"),
		bg(bgTexture, true),
		
		titleLabel(LocalisationManager::getInstance().getTranslation("Credits_Title"), gameFont, Vector2(100.0f, 480.0f)),
		creditsLine1(LocalisationManager::getInstance().getTranslation("Credits_Line1"), gameFont, Vector2(100.0f, 360.0f)),
		creditsLine2(LocalisationManager::getInstance().getTranslation("Credits_Line2"), gameFont, Vector2(100.0f, 300.0f)),
		creditsLine3(LocalisationManager::getInstance().getTranslation("Credits_Line3"), gameFont, Vector2(100.0f, 240.0f)),
		btnBackLabel(LocalisationManager::getInstance().getTranslation("Credits_ReturnButton"), gameFont, Vector2(100.0f, 100.0f)), 
		
		btnBack(nullptr, Vector2(100.0f, 100.0f), Vector2(140.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
				std::cout << "Action: Retour au menu principal" << std::endl;
				SceneManager::getInstance().switchTo("MainScene");
		})
{
		bg.setPosition(Vector2(0.0f, 0.0f));
		bg.setSize(Vector2(800.0f, 600.0f));
}

CreditsScene::~CreditsScene() {}

void CreditsScene::load() {
		std::cout << "Chargement de la scène : " << title << std::endl;
		titleLabel.setText(LocalisationManager::getInstance().getTranslation("Credits_Title"));
		creditsLine1.setText(LocalisationManager::getInstance().getTranslation("Credits_Line1"));
		creditsLine2.setText(LocalisationManager::getInstance().getTranslation("Credits_Line2"));
		creditsLine3.setText(LocalisationManager::getInstance().getTranslation("Credits_Line3"));
		btnBackLabel.setText(LocalisationManager::getInstance().getTranslation("Credits_ReturnButton"));

		eventManager.attach(&btnBack);
}

void CreditsScene::unload() {
		std::cout << "Déchargement de la scène : " << title << std::endl;
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
