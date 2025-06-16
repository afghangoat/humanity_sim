#include "SaveManager.h"

SaveManager::SaveManager(const std::string& file) : fileName(file) {}

void SaveManager::saveFile(World& world) {
	std::ofstream savefile;
	savefile.open(fileName);
	
	savefile << world;
	
	savefile.close();
}

void SaveManager::loadFile(World& world) {
    std::ifstream loaded_file(fileName);
	if (!loaded_file) {
        throw ReadSaveFileFail("Nem sikerült beolvasni a fájlt: "+fileName);
        return;
    }
	
	loaded_file >> world;
	loaded_file.close();
}

void SaveManager::deleteFile() {
	if (std::remove(fileName.c_str()) == 0) {
		warn_text(
			"File deleted: " + fileName,
			"Fájl törölve: " + fileName,
			2
		);
    } else {
		throw ReadSaveFileFail("Nem sikerült kitörölni a fájlt: "+fileName);
    }
}