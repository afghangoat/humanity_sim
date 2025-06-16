#include "House.h"

namespace minerals{
	House::House(int x, int y): Structure(x,y){
		level=1;
		stone_req=4;
		wood_req=2;
		iron_req=3;
		inner_timer=0.0f;
		
		texture_variation=RandomGenerator::get_instance().get_random_int(3)+1;
		std::string strpath=std::string("src/textures/objects/housesand")+std::to_string(texture_variation)+std::string(".png");
		setTexture(strpath);
	}
	
	MINERAL_TYPE House::get_type() const{
		return MINERAL_TYPE::HOUSING;
	}
	
	int House::get_level() const{
		return level;
	}
	void House::set_level(int new_level){
		level=new_level;
	}
	void House::update_logic(float deltaTime){
		inner_timer+=deltaTime;
	}
	
	bool House::try_upgrade(const HumanResources& hr){
		if(stone_req<=0&&wood_req<=0&&iron_req<=0&&level>2){
			return false;
		}
		if(hr.is_there_enough_resource("stone",stone_req)==true&&hr.is_there_enough_resource("wood",wood_req)==true&&hr.is_there_enough_resource("iron",iron_req)==true){
			stone_req=0;
			wood_req=0;
			iron_req=0;
			
			level++;
			upgrade_house();
			
		}
		return false;
	}
	
	void House::upgrade_house(){
		if(level==2){
			stone_req=3;
			wood_req=0;
			iron_req=6;
			
			std::string strpath=std::string("src/textures/objects/housebrick")+std::to_string(texture_variation)+std::string(".png");
			setTexture(strpath);
		} else {
			stone_req=-1;
			wood_req=-1;
			iron_req=-1;
			
			std::string strpath=std::string("src/textures/objects/houseglass")+std::to_string(texture_variation)+std::string(".png");
			setTexture(strpath);
		}
	}
	

}