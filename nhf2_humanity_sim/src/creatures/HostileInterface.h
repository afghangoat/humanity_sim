/**
 * @file HostileInterface.hpp
 * @brief A vadállat interface itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef HOSTILEINTERFACE_HPP
#define HOSTILEINTERFACE_HPP

#include "Living.h"

namespace creature{
	/**
	 * @class HostileInterface
	 * @brief A vadállat entiások interface leírása.
	 *
	 * Ebbe minden deklarálva van, ami ahhoz kell, hogy egy entitás aggresszív legyen.
	 * Van célpontjuk, egységes támadási módszereik és sebzésük.
	 */
	class HostileInterface: public Living{
		protected:
			sf::Vector2f goal; ///< Az célpont entitás pozíciója.
			int damage; ///< A vadállat sebzése.
			float attack_speed; ///< A vadállat támadási sebessége.
			Living* target; ///< A vadállat célpontja.
			
			void try_attack(); ///< Megnézi, hogy milyen közel van a célpontja, ha elég közel van, akkor támad.
			void hostile_run(float deltaTime); ///< Egységes futás logika. Addíg fut a célpont felé míg az vagy meghal vagy elég közel lesz.
			void hostile_walk(float deltaTime); ///< Egységes séta logika. Addíg sétál a célpont felé míg az vagy meghal vagy elég közel lesz. Ezt használja a krokodil, ha ebbe a fázisba meghal a célpont, akkor futás módba vált és egyből keres egy új célpontot.

		public:
			/**
			 * @brief Beállítja a vadállat támadási sebességét és sebzését.
			 * @param newdamage Az új beállított sebzés.
			 * @param newattackspeed Az új beállított sebzési sebesség.
			 */
			void set_hostile_config(int newdamage, float newattackspeed);
			/**
			 * @brief A logikát írja le, ahogy az entitás a világba kiválasztja magának a célpontot.
			 * @param world A világ, amibe a célpontot kell választani.
			 */
			virtual void select_target(World& world)=0;
			virtual ~HostileInterface() = default; ///< Virtuális destruktor.
			
			void retarget(Living* new_target) override;
			Living* check_aggroed() const override;
			
			
	};
}

#endif