#include "Builder.h"

#include "../../World.hpp"

namespace creature{
	Builder::Builder(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("bricks");
	}
	
	void Builder::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					if(RandomGenerator::get_instance().get_random_int(2)==0){
						goal=world.get_position_nearby_town();
					} else {
						goal=world.get_random_house_pos();
					}
					
					if(goal.x!=-1&&goal.y!=-1){
						if(posx<goal.x){
							look_right();
						} else {
							look_left();
						}
						set_state(LIVINGSTATE::RUN);
					} else {
						inner_timer=25.0f;
					}
				}
				break;
			case LIVINGSTATE::RUN:
				humanoid_run(deltaTime);
				break;
			case LIVINGSTATE::WALK:
				humanoid_walk(deltaTime);
				break;
			case LIVINGSTATE::DEATH:
				break;
			case LIVINGSTATE::ATTACKING:
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				if(inner_timer<=0.0f){
					inner_timer=25.0f;
					set_state(LIVINGSTATE::IDLE);
					world.upgrade_house_at(goal.x,goal.y);
				}
				break;
		}
	}
	
	Builder::~Builder(){
		delete profession;
		profession=nullptr;
	}
}