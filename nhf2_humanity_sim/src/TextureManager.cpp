#include "TextureManager.h"
		
TextureManager& TextureManager::getInstance() {
	static TextureManager instance;
	return instance;
}

sf::Texture* TextureManager::loadTexture(const std::string& filename) {
	auto it = textures.find(filename);
	if (it != textures.end()) {
		return &it->second;
	}

    auto& texture = textures[filename];
    if (!texture.loadFromFile(filename)) {
        warn_text(
			"Failed to load texture: " + filename,
			"Nem sikerült betölteni a textúrát: " + filename,
			0
		);
        return nullptr;
    }

    return &texture;
}
sf::Texture TextureManager::getTexture(const std::string& filename) {
	
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		warn_text(
			"Failed to load texture: " + filename,
			"Nem sikerült betölteni a textúrát: " + filename,
			0
		);
        throw std::runtime_error("Fatal");
	}

    return texture;
}


void TextureManager::clear(){
	textures.clear();
}