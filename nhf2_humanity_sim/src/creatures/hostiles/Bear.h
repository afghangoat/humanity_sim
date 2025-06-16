/**
 * @file Bear.hpp
 * @brief A Medve osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef BEAR_HPP
#define BEAR_HPP

#include "../HostileInterface.h"
#include "../../Random_Gen.h"
#include "../../Utils.h"

namespace creature{
	/**
	 * @class Bear
	 * @brief A medve osztály leírása.
	 *
	 * A medve egy aggresszív állat, ami más medvéken kívűl mindent támad. Gyorsan fut.
	 */
	class Bear: public HostileInterface{
		public:
			/**
			 * @brief Idéz egy medvét egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			Bear(int x,int y);
			ENTITY_TYPE get_type() const override;
			
			void die() override;
			void update_logic(World& world,float deltaTime) override;
			void draw_logic(sf::RenderWindow& window,float deltaTime,int offx, int offy) override;
			
			void select_target(World& world) override;
			~Bear(); ///< A medve destruktora.
	};
}

#endif