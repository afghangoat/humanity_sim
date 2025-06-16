#include "AnglerMiner.h"

#include "../../World.hpp"

namespace creature{
	AnglerMiner::AnglerMiner(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier),Fisherman(x,y,gender_modifier), Stonemason(x,y,gender_modifier){
		needs_promotion=false;
		profession->load_profession("saw");
	}
	
	bool AnglerMiner::humanoid_run(float deltaTime){
		float dx = goal.x - posx;
		float dy = goal.y - posy;
		float distance = distance_to(posx, posy, goal.x, goal.y);
		
		if(distance<speed*run_speed_modifier*2.0f){
			inner_timer=6.0f;
			set_state(LIVINGSTATE::DOING_ITS_WORK);
			return true;
		}
		float dirX = dx / distance;
		float dirY = dy / distance;
		posx += dirX * speed * deltaTime*run_speed_modifier;
		posy += dirY * speed * deltaTime*run_speed_modifier;
		
		return false;
	}
	
	bool AnglerMiner::humanoid_walk(float deltaTime){
		return humanoid_run(deltaTime);
	}
	
	void AnglerMiner::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					if(RandomGenerator::get_instance().get_random_int(2)==0){
						try_fishing(world);
					} else {
						fishing=false;
						try_mine(world);
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
					inner_timer=7.0f;
					set_state(LIVINGSTATE::IDLE);
					if(fishing==true){
						world.get_resources().add_resources("food",2+RandomGenerator::get_instance().get_random_int(5));
					} else {
						if(mining_iron==true){
							world.get_resources().add_resources("iron",2);
						} else {
							world.get_resources().add_resources("stone",3+RandomGenerator::get_instance().get_random_int(5));
						}
						world.remove_structure_at(goal.x,goal.y);
					}
					
				}
				break;
		}
	}
	
	AnglerMiner::~AnglerMiner(){
		delete profession;
		profession=nullptr;
	}
}