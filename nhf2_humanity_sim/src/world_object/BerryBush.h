/**
 * @file BerryBush.hpp
 * @brief A bokor osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef BERRYBUSH_HPP
#define BERRYBUSH_HPP

#include "ResourceStructure.h"

namespace minerals{
	/**
	 * @class BerryBush
	 * @brief A bokor osztály leírása. Ételt ad, ha kitermelik.
	 */
	class BerryBush: public ResourceStructure{
		private:
			void refill_berries(); ///< Megváltoztatja a bokor textúráját termedtre és újra ki lehet termelni.
			const float berry_growth_time=360.0; ///< Másodpercben mikor nőjön vissza a bogyó a bokrokra.
		public:
			BerryBush(int x,int y); ///< Konstruktor ami lerakja az erőforrást egy (x,y) pontra.
			
			MINERAL_TYPE get_type() const override;
			
			void update_logic(float deltaTime) override;
			
			bool harvest() override;
			void play_destroy_sound(SoundPlayer& sound_player) const override;
			
	};
}
#endif