#include "Tree.h"

namespace minerals{
	Tree::Tree(int x, int y): ResourceStructure(x,y){
		if(RandomGenerator::get_instance().get_random_int(2)==0){
			setTexture("src/textures/objects/alien_tree.png");
		} else {
			setTexture("src/textures/objects/palm2coconut.png");
		}
	}
	
	MINERAL_TYPE Tree::get_type() const{
		return MINERAL_TYPE::WOOD;
	}
	
	void Tree::update_logic(float deltaTime){
		inner_timer+=deltaTime;
		if(inner_timer>=max_tree_age){
			harvested=true;
		}
	}
	
	void Tree::play_destroy_sound(SoundPlayer& sound_player) const{
		sound_player.play_sound("src/sfx/tree_felling.wav");
	}
}