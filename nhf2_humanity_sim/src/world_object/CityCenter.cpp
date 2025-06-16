#include "CityCenter.h"
#include "../exceptions/WorldExceptions.h"

namespace minerals{
	
	CityCenter::CityCenter(int x, int y): Structure(x,y){
		setTexture("src/textures/objects/city_center.png");
		current_house_count=0;
		settlement_age=0.0f;
	}
	
	bool CityCenter::is_there_room_for_housing(){
		int avail=max_city_size-current_house_count;
		if(avail>0){
			return true;
		}
		return false;
	}
	
	void CityCenter::register_new_house(){
		current_house_count++;
		if(is_there_room_for_housing()==false){
			throw StructureException("Nem fér ba az új ház.");
		}
	}
	
	MINERAL_TYPE CityCenter::get_type() const{
		return MINERAL_TYPE::CITY_CENTER;
	}
	
	void CityCenter::update_logic(float deltaTime){
		settlement_age+=deltaTime;
	}
	
	std::string CityCenter::get_settlement_age(){
		std::string temp_format="";
		temp_format+=(settlement_age/GameConfig::get_instance().day_length);
		temp_format+=" days";
		return temp_format;
	}
}