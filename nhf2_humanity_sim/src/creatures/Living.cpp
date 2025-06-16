#include "Living.h"

namespace creature{
	
	bool Living::setTexture(const std::string& filename) {
		
		sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
		
        if (!sharedTexture) {
            return false;
        }
		
        sprite.setTexture(*sharedTexture);
        return true;
	}
	bool Living::setTheShadow(const std::string& filename){
		
		bool success_shadow=setShadowTexture(filename);
		if(success_shadow==true){
			height_offset=sprite.getGlobalBounds().height;
		}
		
        return success_shadow;
	}
	
	void Living::look_left(){
		facing=FACING::LEFT;
		sprite.setOrigin(0, 0);
		sprite.setScale(1.f, 1.f);
	}
	void Living::look_right(){
		facing=FACING::RIGHT;
		sprite.setOrigin(0, 0); //texRect.width
		sprite.setScale(-1.f, 1.f);
	}

	void Living::setPosition(double x, double y) {
		int moreoffx=0;
		if(facing==FACING::RIGHT){
			moreoffx=get_width();
		}
		
		sprite.setPosition(x+moreoffx, y);
		
	}

	void Living::init_spritesheet_data( int maxframes, double animspeed){
		texture_data.frame_count=maxframes;
		texture_data.animation_speed=animspeed;
		texture_data.current_animation_time=0;
	}
	
	void Living::update_spritesheet(float deltaTime) {
		if(state==LIVINGSTATE::DEATH){
			sprite.setRotation(90.0f);
			death_timer-=deltaTime;
		} else {
			if(hit_timer>0.0f){
				float intensity = std::clamp(hit_timer, 0.0f, 1.0f);

				sf::Color hitColor(255, 255 * (1.0f - intensity), 255 * (1.0f - intensity));
				sprite.setColor(hitColor);
				
				hit_timer-=deltaTime;
			} else {
				sprite.setColor(sf::Color::White);
			}
			texture_data.current_animation_time += texture_data.animation_speed * deltaTime;

			int to_int=texture_data.current_animation_time;
			int frame_index = to_int% texture_data.frame_count;

			int frame_width = sprite.getTexture()->getSize().x / texture_data.frame_count;
			int frame_height = sprite.getTexture()->getSize().y;

			sprite.setTextureRect(sf::IntRect(frame_index * frame_width, 0, frame_width, frame_height));
		}
	}
	
	void Living::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	
	bool Living::needs_drawn(){
		int tw=GameConfig::get_instance().get_screen_width();
		int th=GameConfig::get_instance().get_screen_height();
		
		sf::Vector2f position = sprite.getPosition();
		if (position.x > -MAX_CREATURE_SIZE && position.y > -MAX_CREATURE_SIZE && position.x < tw + MAX_CREATURE_SIZE && position.y < th + MAX_CREATURE_SIZE) {
			return true;
		}
		return false;
	}
	
	int Living::get_width() const{
		
		return sprite.getGlobalBounds().width;
	}
	void Living::shadow_logic(sf::RenderWindow& window, float elapsed_time,int offx, int offy){
		setShadowPosition(posx+offx,posy+offy);
		setShadowDayNightCycle(elapsed_time);
		drawShadow(window);
	}
	
	void Living::damage(Living* dam_by,int amm){
		if(dam_by!=this){
			hit_timer=1.0f;
			health-=amm;
			damaged_by=dam_by;
			
			if(health<=0){
				set_state(LIVINGSTATE::DEATH);
			}
		}
	}
	
	Living::~Living(){
		if(damaged_by!=nullptr){
			damaged_by=nullptr;
		}
		
	}
	
	void Living::set_state(LIVINGSTATE newstate){
		state=newstate;
		switch(state){
			case LIVINGSTATE::IDLE:
				setTexture(texture_data.idle_texture_path);
				break;
			case LIVINGSTATE::RUN:
				setTexture(texture_data.run_texture_path);
				break;
			case LIVINGSTATE::WALK:
				setTexture(texture_data.walk_texture_path);
				break;
			case LIVINGSTATE::DEATH:
				setTexture(texture_data.death_texture);
				death_timer=5.0f;
				break;
			case LIVINGSTATE::ATTACKING:
				setTexture(texture_data.attack_texture_path);
				break;
				
			case LIVINGSTATE::DOING_ITS_WORK:
				setTexture(texture_data.attack_texture_path);
				break;
		}
	}
	
	void Living::retarget(Living* new_target){
		damaged_by=new_target;
	}
	Living* Living::check_aggroed() const{
		return damaged_by;
	}
}