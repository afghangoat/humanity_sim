#include "Crocodile.h"

#include "../../World.hpp"

namespace creature{
	
	Crocodile::Crocodile(int x, int y){
		posx=x;
		posy=y;
		goal.x=x;
		goal.y=y;
		speed=4.5f;
		run_speed_modifier=2.0f;
		inner_timer=0.0f;
		
		int gender_selector=RandomGenerator::get_instance().get_random_int(5);
		if(gender_selector==0){
			gender=ENTITY_GENDER::MALE;
		} else {
			gender=ENTITY_GENDER::FEMALE;
		}
		
		std::string texture_path="src/textures/creatures/crocodile/";
		
		set_idle_texture(texture_path+"croc_idle.png");
		set_attack_texture(texture_path+"croc_atk.png");
		set_walk_texture(texture_path+"croc_walk.png");
		set_run_texture(texture_path+"croc_walk.png");
		set_death_texture(texture_path+"croc_death.png");
		init_spritesheet_data(4,6.0);
		set_state(LIVINGSTATE::IDLE);
		setTheShadow(texture_path+"croc_death.png");
		look_left();
		
		setPosition(x,y);
		max_age=(60.0+(float)(RandomGenerator::get_instance().get_random_int(50)))*GameConfig::get_instance().day_length;
		set_health(130);
		
		set_hostile_config(20,3.0f);
	}
	
	void Crocodile::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					select_target(world);
					
					if(target!=nullptr){
						set_state(LIVINGSTATE::RUN);
					} else {
						
						inner_timer=10.0f;
						goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
						if(posx<goal.x){
							look_right();
						} else {
							look_left();
						}
						set_state(LIVINGSTATE::WALK);
					}
				}
				break;
			case LIVINGSTATE::RUN:
				hostile_run(deltaTime);
				break;
			case LIVINGSTATE::WALK:
				hostile_walk(deltaTime);
				break;
			case LIVINGSTATE::DEATH:
				break;
			case LIVINGSTATE::ATTACKING:
				try_attack();
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				if(inner_timer<=0.0f){
					inner_timer=10.0f;
					set_state(LIVINGSTATE::IDLE);
				}
				break;
		}
	}
	
	void Crocodile::draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			update_spritesheet(deltaTime);
			draw(window);
		}
	}
	
	
	void Crocodile::die(){
		set_state(LIVINGSTATE::DEATH);
	}
	
	ENTITY_TYPE Crocodile::get_type() const {
		return ENTITY_TYPE::ANIMAL;
	}
	
	Crocodile::~Crocodile(){
		damaged_by=nullptr;
		target=nullptr;
	}
	
	void Crocodile::select_target(World& world){
		target=world.get_excluded_entities(ENTITY_TYPE::ROBOTIC);
		
		if(damaged_by!=nullptr){
			target=damaged_by;
		}
	}
}