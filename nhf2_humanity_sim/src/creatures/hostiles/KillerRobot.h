/**
 * @file KillerRobot.hpp
 * @brief A Gyilkos Robot osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef KILLERROBOT_HPP
#define KILLERROBOT_HPP

#include "../HostileInterface.h"
#include "../../Random_Gen.h"
#include "../../Utils.h"

namespace creature{
	/**
	 * @class KillerRobot
	 * @brief A gyilkos robot osztály leírása.
	 *
	 * A gyilkos robot egy ritka ellenség, aminek az az egy célja, hogy kiírtsa az emberiséget, majdnem egy évezredig él (999 évig pontosan), így vagy ő marad, vagy az emberiség.
	 */
	class KillerRobot: public HostileInterface{
		public:
			/**
			 * @brief Idéz egy gyilkos robotot egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			KillerRobot(int x,int y);
			ENTITY_TYPE get_type() const override;
			
			void die() override;
			void update_logic(World& world,float deltaTime) override;
			void draw_logic(sf::RenderWindow& window,float deltaTime,int offx, int offy) override;
			
			void select_target(World& world) override;
			~KillerRobot(); ///< Virtuális destruktor.
	};
}

#endif