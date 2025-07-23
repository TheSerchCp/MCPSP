#include "LanguageManager.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Constructor
LanguageManager::LanguageManager() {

}

// Destructor
LanguageManager::~LanguageManager() {
    // Liberar memoria si fuera necesario
}

void LanguageManager::init()
{
	TextureHelper textureHelper;
	
	if (languageVector.empty()) {
        languageVector.push_back("ca_ca");
        languageVector.push_back("de");
        languageVector.push_back("en_uk");
        languageVector.push_back("en_us");
        languageVector.push_back("es_es");
        languageVector.push_back("fr_fr");
        languageVector.push_back("ja_ja");
        languageVector.push_back("pl_pl");
        languageVector.push_back("pt_br");
        languageVector.push_back("pt_pt");
        languageVector.push_back("ro_ro");
        languageVector.push_back("ru");
        languageVector.push_back("ua_ua");
	}

	if (languageNameVector.empty()) {
        languageNameVector.push_back("Catalan");
        languageNameVector.push_back("Deutsch");
        languageNameVector.push_back("English (United Kingdom)");
        languageNameVector.push_back("English (USA)");
        languageNameVector.push_back("Español (España)");
        languageNameVector.push_back("French");
        languageNameVector.push_back("Japan");
        languageNameVector.push_back("Poland");
        languageNameVector.push_back("Portugues (Brasil)");
        languageNameVector.push_back("Portugues (Portugal)");
        languageNameVector.push_back("Romania");
        languageNameVector.push_back("Russian");
        languageNameVector.push_back("Ukraine");
    }
}

void LanguageManager::getFolderName() {
	textureHelper.LoadLangPath();
	folderNameCD = textureHelper.defaultLangFolder;
}

/// Función para cargar un archivo de traducciones generales
bool LanguageManager::load_language(const std::string &file_path) {
	
	// Abrimos el archivo .txt con el directorio ya definido desde (file_path)
    FILE *file = fopen(file_path.c_str(), "rt");
    if (!file) {
        printf("No se pudo abrir el archivo de traducción: %s\n", file_path.c_str());
        return false;
    }

    // Limpiar las traducciones primero
    translations.clear();

	// Creamos un char con un limite de 64 caracteres
    char line[64];

    while (fgets(line, sizeof(line), file)) {
        Translation trans;
		
		// Leemos el ID y el texto en separados por coma
        char *token = strtok(line, ",");
		
		// Conversor de ID a entero
        trans.id = std::atoi(token);
        token = strtok(NULL, "\n");
        if (token)trans.text = token;
		
		// Agregamos la traduccion al contenedor correspondiente
        translations.push_back(trans);
    }

    fclose(file);
    return true;
}

// Función para cargar un archivo de traducciones de bloques
bool LanguageManager::load_language_blocks(const std::string &file_path) {
    // Abrimos el archivo .txt con el directorio ya definido desde (file_path)
    FILE *file = fopen(file_path.c_str(), "rt");
    if (!file) {
        printf("No se pudo abrir el archivo de traducción: %s\n", file_path.c_str());
        return false;
    }

    // Limpiar las traducciones primero
    translations_blocks.clear();

	// Creamos un char con un limite de 64 caracteres
    char line[64];

    while (fgets(line, sizeof(line), file)) {
        Translation trans;
		
		// Leemos el ID y el texto en separados por coma
        char *token = strtok(line, ",");
		
		// Conversor de ID a entero
        trans.id = std::atoi(token);
        token = strtok(NULL, "\n");
        if (token)trans.text = token;
		
		// Agregamos la traduccion al contenedor correspondiente
        translations_blocks.push_back(trans);
    }

    fclose(file);
    return true;
}

// Función para cargar un archivo de traducciones de ítems
bool LanguageManager::load_language_items(const std::string &file_path) {
    // Abrimos el archivo .txt con el directorio ya definido desde (file_path)
    FILE *file = fopen(file_path.c_str(), "rt");
    if (!file) {
        printf("No se pudo abrir el archivo de traducción: %s\n", file_path.c_str());
        return false;
    }

    // Limpiar las traducciones primero
    translations_items.clear();

	// Creamos un char con un limite de 64 caracteres
    char line[64];

    while (fgets(line, sizeof(line), file)) {
        Translation trans;
		
		// Leemos el ID y el texto en separados por coma
        char *token = strtok(line, ",");
		
		// Conversor de ID a entero
        trans.id = std::atoi(token);
        token = strtok(NULL, "\n");
        if (token)trans.text = token;
		
		// Agregamos la traduccion al contenedor correspondiente
        translations_items.push_back(trans);
    }

    fclose(file);
    return true;
}

// ---### conversor de std a const char ###--- //

const char* LanguageManager::getGeneralTranslation(int id) {
    static std::string translation;
    for (size_t i = 0; i < translations.size(); ++i) {
        if (translations[i].id == id) {
            translation = translations[i].text;
            return translation.c_str();
        }
    }
    translation = "ERROR";
    return translation.c_str();
}

const char* LanguageManager::getBlocksTranslation(int id) {
    static std::string translation;
    for (size_t i = 0; i < translations_blocks.size(); ++i) {
        if (translations_blocks[i].id == id) {
            translation = translations_blocks[i].text;
            return translation.c_str();
        }
    }
    translation = "BLOCK ERROR";
    return translation.c_str();
}

const char* LanguageManager::getItemsTranslation(int id) {
    static std::string translation;
    for (size_t i = 0; i < translations_items.size(); ++i) {
        if (translations_items[i].id == id) {
            translation = translations_items[i].text;
            return translation.c_str();
        }
    }
    translation = "ITEM ERROR";
    return translation.c_str();
}