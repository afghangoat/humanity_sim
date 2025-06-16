/**
 * @file Tree.hpp
 * @brief A fa osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef TREE_HPP
#define TREE_HPP

#include "ResourceStructure.h"
#include "../Random_Gen.h"

namespace minerals{
	/**
	 * @class Tree
	 * @brief A fa osztály leírása. Fát ad, ha kitermelik.
	 */
	class Tree: public ResourceStructure{
		private:
			const float max_tree_age=3600.0; ///< Másodpercben mikor pusztuljon el egy a fa.
		public:
			Tree(int x, int y); ///< Konstruktor ami lerakja az erőforrást egy (x,y) pontra.
		
			MINERAL_TYPE get_type() const override;
			
			void update_logic(float deltaTime) override;
			
			void play_destroy_sound(SoundPlayer& sound_player) const override;
	};
}

#endif