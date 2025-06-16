#include "Iron.h"

namespace minerals{
	Iron::Iron(int x, int y): ResourceStructure(x,y){
		setTexture("src/textures/objects/iron.png");
	}
	
	MINERAL_TYPE Iron::get_type() const{
		return MINERAL_TYPE::IRON;
	}
	
	void Iron::update_logic(float deltaTime){
		inner_timer+=deltaTime;
	}
	void Iron::play_destroy_sound(SoundPlayer& sound_player) const{
		sound_player.play_sound("src/sfx/metal_hit1.wav");
	}
}