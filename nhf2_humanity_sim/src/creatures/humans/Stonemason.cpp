#include "Stonemason.h"

#include "../../World.hpp"

namespace creature{
	Stonemason::Stonemason(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("pickaxe");
		mining_iron=false;
	}
	void Stonemason::try_mine(World& world){
		if(inner_timer<=0.0f){
			minerals::MINERAL_TYPE minerals_finding=minerals::MINERAL_TYPE::STONE;
			mining_iron=false;
			if(RandomGenerator::get_instance().get_random_int(2)==1){
				minerals_finding=minerals::MINERAL_TYPE::IRON;
				mining_iron=true;
			}
			minerals::Structure* currock=world.get_structure_type(minerals_finding);
			if(currock!=nullptr){
				goal.x=currock->posx;
				goal.y=currock->posy;
				if(posx<goal.x){
					look_right();
				} else {
					look_left();
				}
				if(RandomGenerator::get_instance().get_random_int(5)==1){
					set_state(LIVINGSTATE::RUN);
				} else {
					set_state(LIVINGSTATE::WALK);
				}
				
			} else {
				inner_timer=12.0f;
			}
		}
	}
	
	void Stonemason::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				try_mine(world);
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
					
					if(mining_iron==true){
						world.get_resources().add_resources("iron",2);
					} else {
						world.get_resources().add_resources("stone",3+RandomGenerator::get_instance().get_random_int(5));
					}
					
					world.remove_structure_at(goal.x,goal.y);
				}
				break;
		}
	}
	
	Stonemason::~Stonemason(){
		delete profession;
		profession=nullptr;
	}
}