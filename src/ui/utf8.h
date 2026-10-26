#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

/**
 * @brief Fonction utilitaire pour décoder une chaîne UTF-8 en un vecteur de points de code Unicode (uint32_t). Cette fonction parcourt la chaîne UTF-8 et décode chaque séquence d'octets en son point de code Unicode correspondant. Les points de code sont stockés dans un vecteur et renvoyés à l'appelant.
 * 
 * @param text Texte UTF-8 à décoder.
 * @return vector<uint32_t> Vecteur contenant les points de code Unicode décodés à partir de la chaîne UTF-8.
 */
inline vector<uint32_t> DecodeUTF8(
    const string& text)
{
    vector<uint32_t> result;

    for (size_t i = 0; i < text.size();)
    {
        uint32_t c = static_cast<unsigned char>(text[i]);

        if (c <= 0x7F)
        {
            result.push_back(c);
            i++;
        }
        else if ((c & 0xE0) == 0xC0 && i + 1 < text.size())
        {
            c = ((c & 0x1F) << 6) |
                (static_cast<unsigned char>(text[i + 1]) & 0x3F);

            result.push_back(c);
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0 && i + 2 < text.size())
        {
            c = ((c & 0x0F) << 12) |
                ((static_cast<unsigned char>(text[i + 1]) & 0x3F) << 6) |
                (static_cast<unsigned char>(text[i + 2]) & 0x3F);

            result.push_back(c);
            i += 3;
        }
        else if ((c & 0xF8) == 0xF0 && i + 3 < text.size())
        {
            c = ((c & 0x07) << 18) |
                ((static_cast<unsigned char>(text[i + 1]) & 0x3F) << 12) |
                ((static_cast<unsigned char>(text[i + 2]) & 0x3F) << 6) |
                (static_cast<unsigned char>(text[i + 3]) & 0x3F);

            result.push_back(c);
            i += 4;
        }
        else
        {
            // Caractère UTF-8 invalide
            result.push_back(0xFFFD);
            i++;
        }
    }

    return result;
}