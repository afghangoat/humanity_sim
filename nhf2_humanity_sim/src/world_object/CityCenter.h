/**
 * @file CityCenter.hpp
 * @brief A városközpont osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef CITYCENTER_HPP
#define CITYCENTER_HPP

#include "Structure.h"
#include <string>

namespace minerals{
	/**
	 * @class CityCenter
	 * @brief A városközpont osztály leírása. E köré epülnek a házak.
	 */
	class CityCenter: public Structure{
		private:
			static const int max_city_size=16; ///< A maximum ház egy városban.
			int current_house_count; ///< Jelenlegi házak száma, ami a városhoz tartozik.
			float settlement_age; ///< Hány másodperce létezik a városközpont.
			
		public:
			CityCenter(int x, int y); ///< Konstruktor ami lerakja a házat egy (x,y) pontra.
			
			bool is_there_room_for_housing(); ///< Igazat ad vissza, ha lehet még házat építeni köré.
			void register_new_house(); ///< Új házat vesz fel a városhoz.
			
			MINERAL_TYPE get_type() const override;
			void update_logic(float deltaTime) override;
			
			std::string get_settlement_age(); ///< String-ként adja vissza azt, hogy hány másodperces a város.
	};
}
#endif