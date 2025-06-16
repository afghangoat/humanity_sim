#include "HostileInterface.h"

#include "../World.hpp"

namespace creature{
	
	void HostileInterface::set_hostile_config(int newdamage, float newattackspeed){
		target=nullptr;
		damaged_by=nullptr;
		damage=newdamage;
		attack_speed=newattackspeed;
	}
	
	void HostileInterface::try_attack(){
		if(distance_to(posx,posy,target->posx,target->posy)>=speed*run_speed_modifier*2.0f){
			//Entered to goal
			inner_timer=2.0f;
			set_state(LIVINGSTATE::RUN);
		} else {
			if(inner_timer<0.0f){
				inner_timer=attack_speed;
				target->damage(this,damage);
				if(target->get_state()==LIVINGSTATE::DEATH){ //Target died
					target=nullptr;
					inner_timer=3.0f;
					set_state(LIVINGSTATE::DOING_ITS_WORK);
				}
			}
		}
	}
	
	void HostileInterface::hostile_walk(float deltaTime){
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
	}
	
	void HostileInterface::hostile_run(float deltaTime){
		if(distance_to(posx,posy,target->posx,target->posy)<speed*run_speed_modifier*2.0f){
			inner_timer=-0.1f;
			set_state(LIVINGSTATE::ATTACKING);
		} else {
			if(posx<target->posx){
				look_right();
				posx+=speed*deltaTime*run_speed_modifier;
			} else {
				look_left();
				posx-=speed*deltaTime*run_speed_modifier;
			}
			
			if(posy<target->posy){
				posy+=speed*deltaTime*run_speed_modifier;
			} else {
				posy-=speed*deltaTime*run_speed_modifier;
			}
		}
	}
	
	void HostileInterface::retarget(Living* new_target){
		if(damaged_by==target){
			damaged_by=new_target;
		}
		target=new_target;
	}
	Living* HostileInterface::check_aggroed() const{
		return target;
	}
}