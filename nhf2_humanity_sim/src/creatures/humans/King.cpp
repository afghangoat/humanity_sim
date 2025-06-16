#include "King.h"

#include "../../World.hpp"

namespace creature{
	King::King(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("crown");
	}
	
	void King::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					goal=world.get_random_suitable_position(tiles::TILETYPE::MOUNTAIN);
					if(posx<goal.x){
						look_right();
					} else {
						look_left();
					}
					if(RandomGenerator::get_instance().get_random_int(2)==0){
						set_state(LIVINGSTATE::WALK);
					} else {
						set_state(LIVINGSTATE::RUN);
					}
				}
				break;
			case LIVINGSTATE::RUN:
				humanoid_run(deltaTime);
				if(world.getTileAt(posx,posy).get_type()!=tiles::TILETYPE::GRASS){
					goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
					if(posx<goal.x){
						look_right();
					} else {
						look_left();
					}
				}
				break;
			case LIVINGSTATE::WALK:
				humanoid_walk(deltaTime);
				if(world.getTileAt(posx,posy).get_type()==tiles::TILETYPE::WATER){
					goal=world.get_random_suitable_position(tiles::TILETYPE::MOUNTAIN);
					if(posx<goal.x){
						look_right();
					} else {
						look_left();
					}
				}
				break;
			case LIVINGSTATE::DEATH:
				break;
			case LIVINGSTATE::ATTACKING:
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				break;
		}
	}
	
	King::~King(){
		delete profession;
		profession=nullptr;
	}
}