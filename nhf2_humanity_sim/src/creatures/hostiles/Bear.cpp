#include "Bear.h"

#include "../../World.hpp"

namespace creature{
	
	Bear::Bear(int x, int y){
		posx=x;
		posy=y;
		goal.x=x;
		goal.y=y;
		speed=4.0f;
		run_speed_modifier=4.0f;
		inner_timer=0.0f;
		
		int gender_selector=RandomGenerator::get_instance().get_random_int(2);
		if(gender_selector==0){
			gender=ENTITY_GENDER::MALE;
		} else {
			gender=ENTITY_GENDER::FEMALE;
		}
		
		std::string texture_path="src/textures/creatures/bear/";
		
		set_idle_texture(texture_path+"bear_idle.png");
		set_attack_texture(texture_path+"bear_attack.png");
		set_walk_texture(texture_path+"bear_walk.png");
		set_run_texture(texture_path+"bear_walk.png");
		set_death_texture(texture_path+"bear_death.png");
		init_spritesheet_data(4,6.0);
		set_state(LIVINGSTATE::IDLE);
		setTheShadow(texture_path+"bear_death.png");
		look_left();
		
		setPosition(x,y);
		max_age=(40.0+(float)(RandomGenerator::get_instance().get_random_int(50)))*GameConfig::get_instance().day_length;
		set_health(110);
		
		set_hostile_config(14,2.0f);
	}
	
	void Bear::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					select_target(world);
					
					if(target!=nullptr){
						set_state(LIVINGSTATE::RUN);
					} else {
						
						inner_timer=10.0f;
						if(RandomGenerator::get_instance().get_random_int(3)==0){
							goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
							if(posx<goal.x){
								look_right();
							} else {
								look_left();
							}
							set_state(LIVINGSTATE::WALK);
						}
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
					inner_timer=20.0f;
					set_state(LIVINGSTATE::IDLE);
				}
				break;
		}
	}
	
	void Bear::draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			update_spritesheet(deltaTime);
			draw(window);
		}
	}
	
	
	void Bear::die(){
		set_state(LIVINGSTATE::DEATH);
	}
	
	ENTITY_TYPE Bear::get_type() const {
		return ENTITY_TYPE::ANIMAL;
	}
	
	Bear::~Bear(){
		damaged_by=nullptr;
		target=nullptr;
	}
	
	void Bear::select_target(World& world){
		target=world.get_excluded_entities(ENTITY_TYPE::ANIMAL);
		if(damaged_by!=nullptr&&target==nullptr){
			target=damaged_by;
		}
	}
}