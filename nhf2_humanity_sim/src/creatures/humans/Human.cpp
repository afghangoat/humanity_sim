#include "Human.h"

#include "../../World.hpp"

namespace creature{
	
	Human::Human(int x, int y){
		initialize(x,y);
		
		int gender_selector=RandomGenerator::get_instance().get_random_int(2);
		if(gender_selector==0){
			gender=ENTITY_GENDER::MALE;
		} else {
			gender=ENTITY_GENDER::FEMALE;
		}
		needs_to_be_royal=false;
		
		select_texture(x,y,gender_selector);
		max_age=(70.0+(float)(RandomGenerator::get_instance().get_random_int(31)))*GameConfig::get_instance().day_length;
		set_health(100);
		save_name="Human";
	}
	
	Human::Human(int x, int y, ENTITY_GENDER const_gender){
		initialize(x,y);
		
		gender=const_gender;
		int gender_selector=1;
		if(gender==ENTITY_GENDER::MALE){
			gender_selector=0;
		}
		
		select_texture(x,y,gender_selector);
		max_age=(70.0+(float)(RandomGenerator::get_instance().get_random_int(31)))*GameConfig::get_instance().day_length;
		set_health(100);
		save_name="Human";
	}
	std::string Human::get_profession_string(){
		if(profession==nullptr){
			return "?";
		}
		return profession->to_string();
	}
	
	void Human::initialize(int x, int y){
		posx=x;
		posy=y;
		goal.x=x;
		goal.y=y;
		needs_promotion=false;
		if(profession!=nullptr){
			delete profession;
		}
		profession=new Profession("empty");
		speed=7.0f;
		run_speed_modifier=4.0f;
		inner_timer=0.0f;
	}
	
	void Human::select_texture(int x,int y,int gender_selector){
		int look_selector=RandomGenerator::get_instance().get_random_int(3)+1;
		std::string texture_path=std::string("src/textures/creatures/human_")+(gender_selector==0 ? "male" : "female")+'_'+std::to_string(look_selector)+'/';
		
		set_idle_texture(texture_path+"idle.png");
		set_attack_texture(texture_path+"punch.png");
		set_walk_texture(texture_path+"walk.png");
		set_run_texture(texture_path+"run.png");
		set_death_texture(texture_path+"death.png");
		init_spritesheet_data(8,2*3.6); //Nem jó de nem is tragikus
		set_state(LIVINGSTATE::IDLE);
		setTheShadow(texture_path+"death.png");
		look_left();
		
		setPosition(x,y);
	}
	
	bool Human::humanoid_run(float deltaTime){
		if(distance_to(posx,posy,goal.x,goal.y)<speed*run_speed_modifier*2.0f){
			//Célt elérte
			inner_timer=6.0f;
			set_state(LIVINGSTATE::DOING_ITS_WORK);
			return true;
		} else {
			//Célhoz mozgás
			if(posx<goal.x){
				posx+=speed*deltaTime*run_speed_modifier;
			} else {
				posx-=speed*deltaTime*run_speed_modifier;
			}
			
			if(posy<goal.y){
				posy+=speed*deltaTime*run_speed_modifier;
			} else {
				posy-=speed*deltaTime*run_speed_modifier;
			}
		}
		return false;
	}
	
	bool Human::humanoid_walk(float deltaTime){
		if(distance_to(posx,posy,goal.x,goal.y)<speed*2.0f+0.01f){
			//Célt elérte
			inner_timer=4.0f;
			set_state(LIVINGSTATE::DOING_ITS_WORK);
			return true;
		} else {
			//Célhoz mozgás
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
	
	void Human::update_logic(World& world,float deltaTime){
		inner_timer-=deltaTime;
		
		switch(state){
			case LIVINGSTATE::IDLE:
				if(inner_timer<=0.0f){
					minerals::CityCenter* curcenter=world.get_current_city_center();
					if(curcenter==nullptr){//Van-e városközpont?
						set_state(LIVINGSTATE::RUN);
						goal=world.get_random_suitable_position(tiles::TILETYPE::GRASS);
						if(posx<goal.x){
							look_right();
						} else {
							look_left();
						}
					} else {
						needs_promotion=true;
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
				minerals::CityCenter* curcenter=world.get_current_city_center();
				if(curcenter==nullptr){ ///< Még mindíg nincs?
					world.build_city_center_at(posx,posy);
					needs_to_be_royal=true;
				}
				
				set_state(LIVINGSTATE::IDLE);
				break;
		}
	}
	
	void Human::draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy){
		setPosition(posx+offx,posy+offy);
		if(needs_drawn()==true){
			profession->setPosition(posx+offx-4,posy+offy-26);
			profession->draw(window);
			
			update_spritesheet(deltaTime);
			draw(window);
		}
	}
	
	
	void Human::die(){
		set_state(LIVINGSTATE::DEATH);
	}
	
	ENTITY_TYPE Human::get_type() const {
		return ENTITY_TYPE::HUMAN;
	}
	
	Human::~Human(){
		if(profession!=nullptr){
			delete profession;
			profession=nullptr;
		}
		damaged_by=nullptr;
	}
}