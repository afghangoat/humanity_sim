#include "Stone.h"

namespace minerals{
	Stone::Stone(int x, int y): ResourceStructure(x,y){
		setTexture("src/textures/objects/stone.png");
	}
	
	MINERAL_TYPE Stone::get_type() const{
		return MINERAL_TYPE::STONE;
	}
	
	void Stone::update_logic(float deltaTime){
		inner_timer+=deltaTime;
	}
	
	void Stone::play_destroy_sound(SoundPlayer& sound_player) const{
		sound_player.play_sound("src/sfx/mining.wav");
	}
}