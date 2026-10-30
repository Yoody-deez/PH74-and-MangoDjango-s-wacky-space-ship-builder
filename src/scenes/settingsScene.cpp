#include "settingsScene.h"
#include <iostream>
#include <filesystem>

SettingsScene::SettingsScene(Texture* bgTexture, Font* gameFont, SDL_Window* sdlWin)
: Scene("SettingsScene"),
	bg(bgTexture, true),
	m_sdlWin(sdlWin),
	
	titleLabel(LocalisationManager::getInstance().getTranslation("Settings_Title"), gameFont, Vector2(300.0f, 520.0f)),
	lblLanguage(LocalisationManager::getInstance().getTranslation("Settings_LanguageLabel"), gameFont, Vector2(80.0f, 430.0f)),
	lblResolution(LocalisationManager::getInstance().getTranslation("Settings_ResolutionLabel"), gameFont, Vector2(80.0f, 370.0f)),
	lblFullscreen(LocalisationManager::getInstance().getTranslation("Settings_FullscreenLabel"), gameFont, Vector2(80.0f, 310.0f)),
	lblVsync(LocalisationManager::getInstance().getTranslation("Settings_VsyncLabel"), gameFont, Vector2(80.0f, 250.0f)),
	lblMouseSens(LocalisationManager::getInstance().getTranslation("Settings_MouseSensLabel"), gameFont, Vector2(80.0f, 190.0f)),
	lblFov(LocalisationManager::getInstance().getTranslation("Settings_FovLabel"), gameFont, Vector2(80.0f, 130.0f)),

	btnApplyLabel(LocalisationManager::getInstance().getTranslation("Settings_ApplyButton"), gameFont, Vector2(230.0f, 65.0f)),
	btnBackLabel(LocalisationManager::getInstance().getTranslation("Settings_BackButton"), gameFont, Vector2(480.0f, 65.0f)),
	
	langSelector({ 
			LocalisationManager::getInstance().getTranslation("Settings_LanguageSelectorFR"), 
			LocalisationManager::getInstance().getTranslation("Settings_LanguageSelectorEN") 
	}, gameFont, Vector2(550.0f, 430.0f), Vector2(200.0f, 30.0f)), 
	resSelector({ "800x600", "1280x720", "1920x1080" }, gameFont, Vector2(550.0f, 370.0f), Vector2(200.0f, 30.0f)),
	
	chkFullscreen(Vector2(550.0f, 310.0f), Vector2(30.0f, 30.0f), gameFont, ConfigManager::getInstance().isFullscreen()),
	chkVsync(Vector2(550.0f, 250.0f), Vector2(30.0f, 30.0f), gameFont, ConfigManager::getInstance().isVsync()),
	
	sliderMouseSens(0.1f, 5.0f, 0.1f, Vector2(550.0f, 190.0f), Vector2(180.0f, 20.0f), gameFont),
	sliderFov(60.0f, 120.0f, 1.0f, Vector2(550.0f, 130.0f), Vector2(180.0f, 20.0f), gameFont),
	
	btnApply(nullptr, Vector2(200.0f, 60.0f), Vector2(160.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
			auto& config = ConfigManager::getInstance();
			config.setLanguageIndex(langSelector.getCurrentIndex());
			config.setResolutionIndex(resSelector.getCurrentIndex());
			config.setFullscreen(chkFullscreen.isChecked());
			config.setVsync(chkVsync.isChecked());
			config.setMouseSensitivity(sliderMouseSens.getValue());
			config.setFov(sliderFov.getValue());

			int langIdx = config.getLanguageIndex();
			std::string langCode = (langIdx == 1) ? "en" : "fr";
			LocalisationManager::getInstance().setLanguage(langCode);

			updateTexts();

			std::filesystem::path configPath = std::filesystem::path(__FILE__).parent_path().parent_path() / "settings" / "settings.xml";
			config.saveToFile(configPath.string());
			
			if (m_sdlWin) {
					SettingsApplier::applySettings(m_sdlWin);
			}
	}),

	btnBack(nullptr, Vector2(450.0f, 60.0f), Vector2(160.0f, 40.0f), Vector2(0,0), Vector2(0.2f,0.2f), Vector2(0.4f,0.4f), [this]() {
			std::cout << "Action: Retour au menu principal" << std::endl;
			SceneManager::getInstance().switchTo("MainScene");
	})
{
bg.setPosition(Vector2(0.0f, 0.0f));
bg.setSize(Vector2(800.0f, 600.0f));
langSelector.setCurrentIndex(ConfigManager::getInstance().getLanguageIndex());
}

SettingsScene:: ~SettingsScene() {}

void SettingsScene::updateTexts() {
		titleLabel.setText(LocalisationManager::getInstance().getTranslation("Settings_Title"));
		lblLanguage.setText(LocalisationManager::getInstance().getTranslation("Settings_LanguageLabel"));
		lblResolution.setText(LocalisationManager::getInstance().getTranslation("Settings_ResolutionLabel"));
		lblFullscreen.setText(LocalisationManager::getInstance().getTranslation("Settings_FullscreenLabel"));
		lblVsync.setText(LocalisationManager::getInstance().getTranslation("Settings_VsyncLabel"));
		lblMouseSens.setText(LocalisationManager::getInstance().getTranslation("Settings_MouseSensLabel"));
		lblFov.setText(LocalisationManager::getInstance().getTranslation("Settings_FovLabel"));

		btnApplyLabel.setText(LocalisationManager::getInstance().getTranslation("Settings_ApplyButton"));
		btnBackLabel.setText(LocalisationManager::getInstance().getTranslation("Settings_BackButton"));
		
		langSelector.setItems({
				LocalisationManager::getInstance().getTranslation("Settings_LanguageSelectorFR"),
				LocalisationManager::getInstance().getTranslation("Settings_LanguageSelectorEN")
		});
}

void SettingsScene::load() {
		std::cout << "Chargement de la scène : " << title << std::endl;
		updateTexts();

		eventManager.attach(&langSelector);
		eventManager.attach(&resSelector);
		eventManager.attach(&chkFullscreen);
		eventManager.attach(&chkVsync);
		eventManager.attach(&sliderMouseSens);
		eventManager.attach(&sliderFov);
		eventManager.attach(&btnApply);
		eventManager.attach(&btnBack);
}

void SettingsScene::unload() {
		std::cout << "Déchargement de la scène : " << title << std::endl;
		eventManager.detach(&langSelector);
		eventManager.detach(&resSelector);
		eventManager.detach(&chkFullscreen);
		eventManager.detach(&chkVsync);
		eventManager.detach(&sliderMouseSens);
		eventManager.detach(&sliderFov);
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

		lblLanguage.render();
		lblResolution.render();
		lblFullscreen.render();
		lblVsync.render();
		lblMouseSens.render();
		lblFov.render();

		langSelector.render();
		resSelector.render();
		
		chkFullscreen.render();
		chkVsync.render();
		
		sliderMouseSens.render();
		sliderFov.render();

		btnApply.render();
		btnApplyLabel.render();

		btnBack.render();
		btnBackLabel.render();
}
