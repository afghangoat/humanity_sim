/**
 * @file House.hpp
 * @brief A Ház osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "Structure.h"
#include <string>
#include "../Random_Gen.h"
#include "../HumanResources.h"

namespace minerals{
	/**
	 * @class House
	 * @brief A ház osztály leírása. Szinttől függően idéz embereket.
	 */
	class House: public Structure{
		private:
			float inner_timer; ///< Belső időzítő. Méri az eltelt időt a ház lerakása óta.
			int texture_variation; ///< Egy véletlen szám, ami befolyásolja, hogy néz ki a ház.
			
			int stone_req; ///< Mennyi kő kell, hogy a ház elérje a következő szintet.
			int wood_req; ///< Mennyi fa kell, hogy a ház elérje a következő szintet.
			int iron_req; ///< Mennyi vas kell, hogy a ház elérje a következő szintet.
			
			int level; ///< Milyen modern a ház (1-3 -ig).
			
		public:
			House(int x, int y); ///< Konstruktor ami lerakja a házat egy (x,y) pontra.
			
			MINERAL_TYPE get_type() const override;
			void update_logic(float deltaTime) override;
			
			bool try_upgrade(const HumanResources& hr);
			
			int get_level() const;
			void set_level(int new_level);
			void upgrade_house();
	};
}

#endif