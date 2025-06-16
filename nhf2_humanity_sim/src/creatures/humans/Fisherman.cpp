#include "Fisherman.h"

#include "../../World.hpp"

namespace creature{
	Fisherman::Fisherman(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("fishing_rod");
		fishing=false;
	}
	void Fisherman::try_fishing(World& world){
		goal=world.get_random_suitable_position(tiles::TILETYPE::WATER);
		fishing=true;
		if(posx<goal.x){
			look_right();
		} else {
			look_left();
		}
		set_state(LIVINGSTATE::WALK);
	}
	
	void Fisherman::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					try_fishing(world);
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
					inner_timer=5.0f;
					set_state(LIVINGSTATE::IDLE);
					world.get_resources().add_resources("food",2+RandomGenerator::get_instance().get_random_int(4));
				}
				break;
		}
	}
	
	Fisherman::~Fisherman(){
		delete profession;
		profession=nullptr;
	}
}