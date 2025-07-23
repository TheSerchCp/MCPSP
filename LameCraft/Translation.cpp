#include "Translation.h"
#include <cstdio>
#include <cstring>
#include <pspdebug.h>

// Función para leer una traducción desde un archivo .txt
Translation read_translation(FILE *file, int id) {
    Translation trans;

    // Calcular el desplazamiento en bytes (esto no es necesario en archivos .txt)
    fseek(file, id * (sizeof(int) + sizeof(short)), SEEK_SET);

    // Leer el ID
    fread(&trans.id, sizeof(int), 1, file);

    // Leer la longitud del texto
    fread(&trans.length, sizeof(short), 1, file);

    // Leer el texto traducido usando un buffer
    char buffer[64];  // Ajustar el tamaño si es necesario
    fread(buffer, sizeof(char), trans.length, file);
    buffer[trans.length] = '\0';  // Asegurar el fin de cadena

    trans.text = std::string(buffer); // Usar std::string directamente
    return trans;
}

// Función para escribir una traducción en un archivo .txt
void write_translation(FILE *file, int id, const std::string &text) {
    Translation trans;
    trans.id = id;
    trans.length = static_cast<short>(text.size());

    // Escribir los datos en el archivo .txt
    fwrite(&trans.id, sizeof(int), 1, file);
    fwrite(&trans.length, sizeof(short), 1, file);
    fwrite(text.c_str(), trans.length, 1, file);
}
