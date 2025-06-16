#include "Goat.h"

#include "../World.hpp"

namespace creature{
	
	Goat::Goat(int x, int y){
		posx=x;
		posy=y;
		goal.x=x;
		goal.y=y;
		speed=7.5f;
		run_speed_modifier=3.0f;
		inner_timer=0.0f;
		
		int gender_selector=RandomGenerator::get_instance().get_random_int(2);
		if(gender_selector==0){
			gender=ENTITY_GENDER::MALE;
		} else {
			gender=ENTITY_GENDER::FEMALE;
		}
		
		std::string texture_path="src/textures/creatures/black_goat/";
		
		set_idle_texture(texture_path+"black_goat.png");
		set_attack_texture(texture_path+"black_goat_attack.png");
		set_walk_texture(texture_path+"black_goat_walk.png");
		set_run_texture(texture_path+"black_goat_walk.png");
		set_death_texture(texture_path+"blackgoatdeath.png");
		init_spritesheet_data(3,5.5);
		set_state(LIVINGSTATE::IDLE);
		setTheShadow(texture_path+"blackgoatdeath.png");
		look_left();
		
		setPosition(x,y);
		
		max_age=(30.0+(float)(RandomGenerator::get_instance().get_random_int(31)))*GameConfig::get_instance().day_length;
		set_health(50);
	}
	
	bool Goat::goat_idle(World& world){
		if(inner_timer<=0.0f){
			if(RandomGenerator::get_instance().get_random_int(2)==0){
				set_state(LIVINGSTATE::WALK);
			} else {
				set_state(LIVINGSTATE::RUN);
			}
			
			goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
			if(posx<goal.x){
				look_right();
			} else {
				look_left();
			}
			inner_timer=10.0f;
			
		}
		return true;
	}
	
	bool Goat::goat_run(float deltaTime){
		if(distance_to(posx,posy,goal.x,goal.y)<speed*run_speed_modifier*2.0f){
			set_state(LIVINGSTATE::DOING_ITS_WORK);
			return true;
		} else {
			if(posx<goal.x){
				posx+=speed*deltaTime*run_speed_modifier;
			} else {
				posx-=speed*deltaTime*run_speed_modifier;
			}
			
			if(posy<goal.y){
				posy+=speed*deltaTime*run_speed_modifier;
			} else {
				posy-=speed*deltaTime*run_speed_modifier;
			}
		}
		return false;
	}
	
	bool Goat::goat_walk(float deltaTime){
		if(distance_to(posx,posy,goal.x,goal.y)<speed*2.0f+0.01f){
			set_state(LIVINGSTATE::DOING_ITS_WORK);
			return true;
		} else {
			if(posx<goal.x){
				posx+=speed*deltaTime;
			} else {
				posx-=speed*deltaTime;
			}
			
			if(posy<goal.y){
				posy+=speed*deltaTime;
			} else {
				posy-=speed*deltaTime;
			}
		}
		return false;
	}
	
	void Goat::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				goat_idle(world);
				break;
			case LIVINGSTATE::RUN:
				goat_run(deltaTime);
				break;
			case LIVINGSTATE::WALK:
				goat_walk(deltaTime);
				break;
			case LIVINGSTATE::DEATH:
				break;
			case LIVINGSTATE::ATTACKING:
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				inner_timer=10.0f;
				set_state(LIVINGSTATE::IDLE);
				break;
		}
	}
	
	void Goat::draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			update_spritesheet(deltaTime);
			draw(window);
		}
	}
	
	
	void Goat::die(){
		set_state(LIVINGSTATE::DEATH);
	}
	
	ENTITY_TYPE Goat::get_type() const {
		return ENTITY_TYPE::ANIMAL;
	}
	
	Goat::~Goat(){
		damaged_by=nullptr;
	}
}