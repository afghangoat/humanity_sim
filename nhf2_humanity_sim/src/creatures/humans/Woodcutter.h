/**
 * @file Woodcutter.hpp
 * @brief A favágó szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef WOODCUTTER_HPP
#define WOODCUTTER_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Woodcutter
	 * @brief A favágó szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember fákat keres és kivágja őket, így fát szerez.
	 */
	class Woodcutter: public Human{
		public:
			/**
			 * @brief Inicializál egy favágót egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A favágó neme.
			 */
			Woodcutter(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Woodcutter(); ///< A favágó destruktora.
			
			
	};
}

#endif