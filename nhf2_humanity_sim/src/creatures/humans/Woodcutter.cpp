#include "Woodcutter.h"

#include "../../World.hpp"

namespace creature{
	Woodcutter::Woodcutter(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("axe");
	}
	
	void Woodcutter::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					minerals::Structure* curtree=world.get_structure_type(minerals::MINERAL_TYPE::WOOD);
					if(curtree!=nullptr){
						goal.x=curtree->posx;
						goal.y=curtree->posy;
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
					inner_timer=18.0f;
					set_state(LIVINGSTATE::IDLE);
					world.get_resources().add_resources("wood",3+RandomGenerator::get_instance().get_random_int(5));
					world.remove_structure_at(goal.x,goal.y);
				}
				break;
		}
	}
	
	Woodcutter::~Woodcutter(){
		delete profession;
		profession=nullptr;
	}
}