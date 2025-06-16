#include "Structure.h"

namespace minerals{
	Structure::Structure(int x, int y): posx(x), posy(y){
	}
	
	bool Structure::setTexture(const std::string& filename) {
		
		sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
		
        if (!sharedTexture) {
            return false;
        }
		
        sprite.setTexture(*sharedTexture);
		
		bool success_shadow=setShadowTexture(filename);
		if(success_shadow==true){
			height_offset=sprite.getGlobalBounds().height;
		}
		
        return success_shadow;
	}

	void Structure::setPosition(double x, double y) {
		sprite.setPosition(x, y);
	}
	
	void Structure::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	
	bool Structure::needs_drawn(){
		int tw=GameConfig::get_instance().get_screen_width();
		int th=GameConfig::get_instance().get_screen_height();
		
		sf::Vector2f position = sprite.getPosition();
		if (position.x > -MAX_OBJECT_SIZE && position.y > -MAX_OBJECT_SIZE && position.x < tw + MAX_OBJECT_SIZE && position.y < th + MAX_OBJECT_SIZE) {
			return true;
		}
		return false;
	}
	void Structure::draw_logic(sf::RenderWindow& window,float elapsed_time,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			draw(window);
			
			setShadowPosition(posx+offx,posy+offy);
			setShadowDayNightCycle(elapsed_time);
			
			drawShadow(window);
		}
	}

}