#pragma once
#include <string>
#include <glad/gl.h>
#include "resource.h"

#include "stb_truetype.h"

using namespace std;

/**
 * @brief Classe représentant une police de caractères TrueType. Cette classe est responsable du chargement d'une police à partir d'un fichier, de la création d'un atlas de caractères et de la gestion des informations nécessaires pour le rendu du texte à l'écran.
 */
class Font : public Resource {
private:
    // CONSTANTES PRIVÉS

    static constexpr int FIRST_CHAR = 32; // Premier caractère ASCII à inclure dans l'atlas de caractères (espace)
    static constexpr int NUM_CHARS = 224; // Nombre total de caractères à inclure dans l'atlas de caractères (de l'espace à 255)
    static constexpr int ATLAS_WIDTH = 512; // Largeur de l'atlas de caractères
	static constexpr int ATLAS_HEIGHT = 512; // Hauteur de l'atlas de caractères

    // MEMBRES PRIVÉS

    unsigned char* ttfBuffer; // Tampon pour stocker les données de la police TrueType
    stbtt_fontinfo fontInfo; // Structure contenant les informations sur la police TrueType
    unsigned int atlasTextureID; // Identifiant de la texture OpenGL pour l'atlas de caractères
    stbtt_bakedchar cdata[NUM_CHARS]; // Tableau pour stocker les informations de chaque caractère cuit dans l'atlas
public:

    /** 
     * @brief Constructeur de la classe Font.
     * @param path Le chemin vers le fichier de la police TrueType.
     */
    Font(const std::string& path);

    /**
     * @brief Destructeur de la classe Font. Libère les ressources allouées pour le tampon de police et la texture de l'atlas.
     */
    ~Font() override;

    /** 
     * @brief Lie la texture de l'atlas de caractères à l'unité de texture OpenGL actuelle.
     */
    void bindAtlas() const;

    /** 
     * @brief Délie la texture de l'atlas de caractères de l'unité de texture OpenGL actuelle.
     */
    void unbindAtlas() const;

    /** 
     * @brief Renvoie un pointeur vers le tableau des caractères cuits dans l'atlas.
     * @return Un pointeur vers le tableau des caractères cuits.
     */
    const stbtt_bakedchar* getBakedChars() const;

    /** 
     * @brief Vérifie si la police contient un glyphe pour un point de code donné. Attention, vérifie si le point de code est dans la plage, mais pas si le glyphe est réellement présent dans la police.
     * @param codepoint Le point de code à vérifier.
     * @return true si la police contient le glyphe, false sinon.
     */
    bool hasGlyph(uint32_t codepoint) const;

    /** 
     * @brief Renvoie l'index du glyphe correspondant à un point de code donné.
     * @param codepoint Le point de code pour lequel obtenir l'index du glyphe.
     * @return L'index du glyphe correspondant au point de code, ou -1 si le glyphe n'existe pas.
     */
    int getGlyphIndex(uint32_t codepoint) const;

    /** 
     * @brief Vérifie si la police a été chargée avec succès.
     * @return true si la police est chargée, false si elle ne l'est pas.
     */
    bool isLoaded() const;
};