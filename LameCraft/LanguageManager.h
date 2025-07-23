#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "Translation.h"
#include "TextureHelper.h" //Solo para llamar al archivo guardado ):
#include <vector>
#include <string>

class LanguageManager {
public:
    LanguageManager();  // Constructor
    ~LanguageManager();  // Destructor

	void init();
	void clean_memory();
	void getFolderName();
	
	// TextureHelper
	TextureHelper textureHelper;
	
	// String para guardar el nombre de la carpeta
	std::string folderNameCD;
	
	// Vectores para los datos, ya que no funciona con arrays
	std::vector<std::string> languageVector;
	std::vector<std::string> languageNameVector;

    // Función para cargar un archivo binario de traducciones
    bool load_language(const std::string &file_path);
    bool load_language_blocks(const std::string &file_path);
    bool load_language_items(const std::string &file_path);

    // Función para llamar y/o obtener una traducción por ID
	const char* getGeneralTranslation(int id);
	const char* getBlocksTranslation(int id);
	const char* getItemsTranslation(int id);

private:
    std::vector<Translation> translations;  // Contenedor de traducciones cargadas: general
    std::vector<Translation> translations_blocks;  // Contenedor de traducciones cargadas: blocks
    std::vector<Translation> translations_items;  // Contenedor de traducciones cargadas: items
};

#endif // LANGUAGEMANAGER_H