/**
 * @file Builder.hpp
 * @brief Az építész szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef BUILDER_HPP
#define BUILDER_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Builder
	 * @brief Az építész szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember épületeket fejleszt magasabb szintekre. Ha nincs épület akkor épít még.
	 */
	class Builder: public Human{
		public:
			/**
			 * @brief Inicializál egy építészt egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier Az építész neme.
			 */
			Builder(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Builder(); ///< Az építész destruktora.
			
			
	};
}

#endif