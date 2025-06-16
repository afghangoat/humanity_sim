#include "Tile.h"

namespace tiles{
	bool Tile::setTexture(const std::string& filename) {
		sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
		
        if (!sharedTexture) {
            return false;
        }
		
        sprite.setTexture(*sharedTexture);
        return true;
	}

	void Tile::setPosition(double x, double y) {
		sprite.setPosition(x, y);
	}

	void Tile::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	
	void Tile::init(TILETYPE newtype){
		inner_type=newtype;
		switch(inner_type){
			case TILETYPE::GRASS:
				setTexture("src/textures/tiles/grass.png");
				break;
			case TILETYPE::WATER:
				setTexture("src/textures/tiles/water.png");
				break;
			case TILETYPE::MOUNTAIN:
				setTexture("src/textures/tiles/mountain.png");
				break;
			
		}
		
	}
	
	TILETYPE Tile::get_type() const{
		return inner_type;
	}
}