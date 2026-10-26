#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../graphics/font.h"
#include "utf8.h"
//#include "../system/localisationManager.h"

// TODO: Vérifier si isLocalized est nécessaire.

using namespace std;

/**
 * @brief Classe représentant un label dans l'interface utilisateur. Un label est un élément visuel qui affiche du texte ou une image à l'écran. Il peut être utilisé pour afficher des informations, des titres, des messages ou tout autre contenu textuel ou graphique.
 */
class Label : public VisualControl {
private:
    string text; // Texte affiché par le label. Peut être vide si le label est basé sur une texture.
    string textID; // Identifiant de localisation pour le texte du label. Utilisé pour récupérer la traduction appropriée à partir du LocalisationManager.
    vector<uint32_t> codepoints; // Points de code Unicode décodés à partir du texte UTF-8.
    bool isLocalized; // Indique si le texte du label doit être localisé en fonction de l'identifiant de localisation. Si true, le texte sera récupéré à partir du LocalisationManager en utilisant textID.
    Font* textFont; // Police utilisée pour rendre le texte du label. Peut être nullptr si le label est basé sur une texture.
    Texture* labelTexture; // Texture utilisée pour afficher une image dans le label. Peut être nullptr si le label est basé sur du texte.
    unsigned int VAO, VBO; // Identifiants OpenGL pour le Vertex Array Object (VAO) et le Vertex Buffer Object (VBO) utilisés pour le rendu du label. Ces objets sont utilisés pour stocker les données de vertex et les configurations de rendu.

public:
    /**
     * @brief Constructeur d'un label. Il peut être initialisé avec une texture ou avec du texte et une police. Le label peut également être configuré pour être localisé en fonction d'un identifiant de localisation.
     * 
     * @param tex Texture à utiliser pour le label.
     * @param pos Vecteur de position du label à l'écran.
     * @param s Vecteur de taille du label à l'écran.
     * @param t Texte à afficher dans le label.
     * @param f Police à utiliser pour le texte du label.
     * @param id Identifiant de localisation pour le texte du label.
     */
    Label(Texture* tex, Vector2 pos, Vector2 s);
    Label(const string& t, Font* f, Vector2 pos);
    Label(const string& id, Font* f, Vector2 pos, bool localized);

    /**
     * @brief Initialise le quad utilisé pour le rendu du label. Cette méthode configure les données de vertex et les buffers OpenGL nécessaires pour afficher le label à l'écran.
     */
    void initQuad();

    /**
     * @brief Destructeur du label. Libère les ressources OpenGL associées au label, telles que le Vertex Array Object (VAO) et le Vertex Buffer Object (VBO).
     */
    ~Label();

    /**
     * @brief Assigne le texte du label. Ne doit pas être utilisé si le Label est basé sur une texture. Si le label est configuré pour être localisé, le texte sera récupéré à partir du LocalisationManager en utilisant l'identifiant de localisation assigné au label.
     * 
     * @param newText Nouveau texte à afficher dans le label.
     */
    void setText(const string& newText);
    
    /**
     * @brief Renvoie le texte actuellement affiché par le label.
     * 
     * @return Texte du label.
     */
    const string& getText() const;
    
    /**
     * @brief Assigne un identifiant de localisation au Label. Si le label est configuré pour être localisé, le texte sera récupéré à partir du LocalisationManager en utilisant cet identifiant.
     * @param id Identifiant de localisation à assigner au label. Cet identifiant sera utilisé pour récupérer la traduction appropriée à partir du LocalisationManager.
     */
    void setTextID(const string& id);
    
    /**
     * @brief Met à jour le texte du label en fonction de l'identifiant de localisation. Cette méthode récupère la traduction appropriée à partir du LocalisationManager en utilisant l'identifiant de localisation assigné au label.
     */
    void updateLocalizedText();

    /**
     * @brief Assigne une texture au label.
     * @param tex Texture à assigner au label.
     */
    void setTexture(Texture* tex);

    /**
     * @brief Rend le label à l'écran. Cette méthode configure les paramètres OpenGL nécessaires pour afficher le label, puis effectue le rendu en fonction du texte ou de la texture assignée au label.
     */
    void render() override;


};