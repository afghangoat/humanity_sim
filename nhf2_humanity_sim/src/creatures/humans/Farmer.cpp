#include "Farmer.h"

#include "../../World.hpp"

namespace creature{
	Farmer::Farmer(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("scythe");
	}
	
	void Farmer::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					minerals::Structure* curfood_source=world.get_structure_type(minerals::MINERAL_TYPE::FOOD);
					if(curfood_source!=nullptr){
						goal.x=curfood_source->posx;
						goal.y=curfood_source->posy;
						if(posx<goal.x){
							look_right();
						} else {
							look_left();
						}
						set_state(LIVINGSTATE::RUN);
					} else {
						inner_timer=10.0f;
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
					inner_timer=13.0f;
					set_state(LIVINGSTATE::IDLE);
					world.get_resources().add_resources("food",4+RandomGenerator::get_instance().get_random_int(5));
					world.remove_structure_at(goal.x,goal.y);
				}
				break;
		}
	}
	
	Farmer::~Farmer(){
		delete profession;
		profession=nullptr;
	}
}