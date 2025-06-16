/**
 * @file Stone.hpp
 * @brief A Kő osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef STONE_HPP
#define STONE_HPP

#include "ResourceStructure.h"
#include "../Random_Gen.h"

namespace minerals{
	/**
	 * @class Stone
	 * @brief A kő osztály leírása. követ ad, amikor kitermelik.
	 */
	class Stone: public ResourceStructure{
		public:
			Stone(int x, int y); ///< Konstruktor ami lerakja a házat egy (x,y) pontra.
		
			MINERAL_TYPE get_type() const override;
			
			void update_logic(float deltaTime) override;
			
			void play_destroy_sound(SoundPlayer& sound_player) const override;
	};
}

#endif