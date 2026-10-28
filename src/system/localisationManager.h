#pragma once
#include <unordered_map>
#include <string>

using namespace std;

/**
 * @brief Gestionnaire de la localisation et des traductions dans le jeu. Classe en singleton pour assurer qu'il n'y a qu'une seule instance de LocalisationManager.
 */
class LocalisationManager
{
private:
	unordered_map<string, string> translations;
	string currentLanguage;

	/**
	 * @brief Constructeur privé du LocalisationManager pour empêcher l'instanciation directe.
	 */
	LocalisationManager();
public:
	/**
	 * @brief Récupère l'instance unique du LocalisationManager.
	 * @return Référence à l'instance unique du LocalisationManager.
	 */
	static LocalisationManager& getInstance();

	/**
	 * @brief Destructeur du LocalisationManager
	 */
	~LocalisationManager();

	LocalisationManager(const LocalisationManager&) = delete;
	LocalisationManager& operator=(const LocalisationManager&) = delete;

	/**
	 * @brief Définit la langue courante. La langue doit être spécifiée en deux lettres insensibles à la casse. Ex: "fr" pour le français, "en" pour l'anglais. Cette langue sera utilisée pour trouver un chemin d'accès vers le dictionnaire correspondant.
	 * @param language La langue à définir. S'écrit en deux lettres insensibles à la casse. Ex: "fr" pour le français, "en" pour l'anglais.
	 * @return true si la langue a été définie avec succès, false sinon.
	 */
	bool setLanguage(const string& language);

	// TODO: Ajouter une traduction par défaut si la clé n'est pas trouvée, ou une gestion d'erreur plus appropriée.
	/**
	 * @brief Récupère la traduction d'une clé donnée.
	 * @param key La clé pour laquelle récupérer la traduction.
	 * @return La traduction correspondante à la clé, ou un message d'erreur si aucune traduction n'est trouvée.
	 */
	string getTranslation(const string& key) const;
};
