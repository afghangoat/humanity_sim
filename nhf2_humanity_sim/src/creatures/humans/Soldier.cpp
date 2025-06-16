#include "Soldier.h"

#include "../../World.hpp"

namespace creature{
	Soldier::Soldier(int x, int y,ENTITY_GENDER gender_modifier): Human(x, y, gender_modifier){
		needs_promotion=false;
		profession->load_profession("sword");
		target=nullptr;
		damage=15;
		attack_speed=1.5f;
		
	}
	
	bool Soldier::humanoid_run(float deltaTime){
		if(target==nullptr){
			set_state(LIVINGSTATE::IDLE);
		}
		if(posx>goal.x){
			look_right();
		} else {
			look_left();
		}
		if(distance_to(posx,posy,target->posx,target->posy)<speed*run_speed_modifier*2.0f){
			//Entered to goal
			inner_timer=-0.1f;
			set_state(LIVINGSTATE::ATTACKING);
		} else {
			
			//Move towards goal
			if(posx<target->posx){
				posx+=speed*deltaTime*run_speed_modifier;
			} else {
				posx-=speed*deltaTime*run_speed_modifier;
			}
			
			if(posy<target->posy){
				posy+=speed*deltaTime*run_speed_modifier;
			} else {
				posy-=speed*deltaTime*run_speed_modifier;
			}
		}
		return false;
	}
	
	bool Soldier::humanoid_walk(float deltaTime){
		if(target==nullptr){
			set_state(LIVINGSTATE::IDLE);
		}
		if(posx>goal.x){
			look_right();
		} else {
			look_left();
		}
		if(distance_to(posx,posy,goal.x,goal.y)<speed*2.0f+0.01f){
			inner_timer=8.0f;
			set_state(LIVINGSTATE::DOING_ITS_WORK);
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
	void Soldier::attacking(){
		if(target==nullptr){
			set_state(LIVINGSTATE::IDLE);
		}
		if(distance_to(posx,posy,target->posx,target->posy)>=speed*run_speed_modifier*2.0f){
			//Célba ért
			inner_timer=2.0f;
			set_state(LIVINGSTATE::RUN);
		} else {
			if(inner_timer<0.0f){
				inner_timer=attack_speed;
				if(target!=nullptr){
					target->damage(this,damage);
					if(target->get_state()==LIVINGSTATE::DEATH){ //Célpont meghalt
						target=nullptr;
						inner_timer=8.0f;
						set_state(LIVINGSTATE::DOING_ITS_WORK);
					}
				} else {
					inner_timer=8.0f;
					set_state(LIVINGSTATE::DOING_ITS_WORK);
				}
				
			}
		}
	}
	
	void Soldier::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					target=world.get_excluded_entities(ENTITY_TYPE::HUMAN);
					if(target==this){
						return;
					}
					if(damaged_by!=nullptr){
						target=damaged_by;
					}
					
					if(target!=nullptr){
						set_state(LIVINGSTATE::RUN);
					} else {
						inner_timer=10.0f;
						goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
						if(posx>goal.x){
							look_right();
						} else {
							look_left();
						}
						set_state(LIVINGSTATE::WALK);
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
				attacking();
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				if(inner_timer<=0.0f){
					inner_timer=10.0f;
					set_state(LIVINGSTATE::IDLE);
				}
				break;
		}
	}
	
	Soldier::~Soldier(){
		delete profession;
		profession=nullptr;
		target=nullptr;
	}
}