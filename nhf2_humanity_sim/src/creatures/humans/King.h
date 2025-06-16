/**
 * @file King.hpp
 * @brief A király szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef KING_HPP
#define KING_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class King
	 * @brief A király szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember nem sokat csinál. A király szakma csak indikálja, hogy ő alapította a várost. Alapítást után csak őrülten bolyong a világba.
	 */
	class King: public Human{
		public:
			/**
			 * @brief Inicializál egy királyt egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A király neme.
			 */
			King(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~King(); ///< A király destruktora.
			
			
	};
}

#endif