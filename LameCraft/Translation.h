#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <string>

struct Translation {
    int id;            // ID único de la traducción
    short length;      // Longitud del texto
    std::string text;  // Texto traducido
};

// Función para leer una traducción por ID desde un archivo binario
Translation read_translation(FILE *file, int id);

// Función para escribir una traducción en un archivo binario
void write_translation(FILE *file, int id, const std::string &text);

#endif // TRANSLATION_H
