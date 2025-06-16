/**
 * @file Iron.hpp
 * @brief A Vasérc osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef IRON_HPP
#define IRON_HPP

#include "ResourceStructure.h"
#include "../Random_Gen.h"

namespace minerals{
	/**
	 * @class Iron
	 * @brief A vasérc osztály leírása. Vasat ad, amikor kitermelik.
	 */
	class Iron: public ResourceStructure{
		public:
			Iron(int x, int y); ///< Konstruktor ami lerakja a házat egy (x,y) pontra.
		
			MINERAL_TYPE get_type() const override;
			
			void update_logic(float deltaTime) override;
			
			void play_destroy_sound(SoundPlayer& sound_player) const override;
	};
}

#endif