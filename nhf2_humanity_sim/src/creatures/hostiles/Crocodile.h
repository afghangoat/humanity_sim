/**
 * @file Crocodile.hpp
 * @brief A krokodil osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef CROCODILE_HPP
#define CROCODILE_HPP

#include "../HostileInterface.h"
#include "../../Random_Gen.h"
#include "../../Utils.h"

namespace creature{
	/**
	 * @class Crocodile
	 * @brief A krokodil osztály leírása.
	 *
	 * A krokodil egy aggresszív állat, ami mindent megeszik a robotokon kívűl. Lassan mozog.
	 */
	class Crocodile: public HostileInterface{
		public:
			/**
			 * @brief Idéz egy krokodilt egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			Crocodile(int x,int y);
			ENTITY_TYPE get_type() const override;
			
			void die() override;
			void update_logic(World& world,float deltaTime) override;
			void draw_logic(sf::RenderWindow& window,float deltaTime,int offx, int offy) override;
			
			void select_target(World& world) override;
			~Crocodile(); ///< A krododil destruktora.
	};
}

#endif