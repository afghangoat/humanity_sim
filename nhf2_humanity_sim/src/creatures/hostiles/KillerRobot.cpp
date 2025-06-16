#include "KillerRobot.h"

#include "../../World.hpp"

namespace creature{
	
	KillerRobot::KillerRobot(int x, int y){
		posx=x;
		posy=y;
		goal.x=x;
		goal.y=y;
		speed=6.0f;
		run_speed_modifier=2.0f;
		inner_timer=0.0f;
		
		gender=ENTITY_GENDER::MALE;
		
		std::string texture_path="src/textures/creatures/killer_robot/";
		
		set_idle_texture(texture_path+"idle.png");
		set_attack_texture(texture_path+"idle.png");
		set_walk_texture(texture_path+"walk.png");
		set_run_texture(texture_path+"walk.png");
		set_death_texture(texture_path+"death.png");
		init_spritesheet_data(8,7.0);
		set_state(LIVINGSTATE::IDLE);
		setTheShadow(texture_path+"death.png");
		look_left();
		
		setPosition(x,y);
		max_age=999.0*GameConfig::get_instance().day_length;
		set_health(200);
		
		set_hostile_config(30,1.0f);
	}
	
	void KillerRobot::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					select_target(world);
					
					if(target!=nullptr){
						set_state(LIVINGSTATE::RUN);
					} else {
						inner_timer=8.0f;
					}
				}
				break;
			case LIVINGSTATE::RUN:
				hostile_run(deltaTime);
				break;
			case LIVINGSTATE::WALK:
				hostile_walk(deltaTime);
				break;
			case LIVINGSTATE::DEATH:
				break;
			case LIVINGSTATE::ATTACKING:
				try_attack();
				break;
			case LIVINGSTATE::DOING_ITS_WORK:
				if(inner_timer<=0.0f){
					inner_timer=20.0f;
					set_state(LIVINGSTATE::IDLE);
				}
				break;
		}
	}
	
	void KillerRobot::draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			update_spritesheet(deltaTime);
			draw(window);
		}
	}
	
	
	void KillerRobot::die(){
		set_state(LIVINGSTATE::DEATH);
	}
	
	ENTITY_TYPE KillerRobot::get_type() const {
		return ENTITY_TYPE::ROBOTIC;
	}
	
	KillerRobot::~KillerRobot(){
		damaged_by=nullptr;
		target=nullptr;
	}
	
	void KillerRobot::select_target(World& world){
		target=world.get_excluded_entities(ENTITY_TYPE::ROBOTIC);
		if(damaged_by!=nullptr&&target==nullptr){
			target=damaged_by;
		}
	}
}