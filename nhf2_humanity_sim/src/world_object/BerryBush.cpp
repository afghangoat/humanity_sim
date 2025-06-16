#include "BerryBush.h"

namespace minerals{
	BerryBush::BerryBush(int x, int y): ResourceStructure(x,y){
		setTexture("src/textures/objects/bush.png");
	}
	MINERAL_TYPE BerryBush::get_type() const{
		return MINERAL_TYPE::FOOD;
	}
	
	void BerryBush::update_logic(float deltaTime){
		inner_timer+=deltaTime;
		if(inner_timer>=berry_growth_time){
			inner_timer=0.0f;
			refill_berries();
		}
	}
	
	bool BerryBush::harvest(){
		bool success=false;
		if(harvested==false){
			needs_remove=true;
			setTexture("src/textures/objects/bush_empty.png");
			success=true;
			harvested=true;
			return true;
		}
		
		return success;
		
	}
	
	void BerryBush::refill_berries(){
		if(harvested==true){
			setTexture("src/textures/objects/bush.png");
			harvested=false;
		}
	}
	void BerryBush::play_destroy_sound(SoundPlayer& sound_player) const{
		sound_player.play_sound("src/sfx/berrybush_pick.wav");
	}
}