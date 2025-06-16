/**
 * @file Farmer.hpp
 * @brief A farmer szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef FARMER_HPP
#define FARMER_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Farmer
	 * @brief A farmer szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember bokrokat keres és kitermeli őket ezzel ételt szerez.
	 */
	class Farmer: public Human{
		public:
			/**
			 * @brief Inicializál egy farmert egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A farmer neme.
			 */
			Farmer(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Farmer(); ///< A farmer destruktora.
			
			
	};
}

#endif