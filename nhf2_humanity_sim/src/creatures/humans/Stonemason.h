/**
 * @file Stonemason.hpp
 * @brief A bányász szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef STONEMASON_HPP
#define STONEMASON_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Stonemason
	 * @brief A bányász szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember követ vagy vasat keres és kitermeli őket, így követ és vasat szerez.
	 */
	class Stonemason: virtual public Human{
		protected:
			bool mining_iron; ///< Vasat bányászik-e? Ha hamis, akkor követ bányászik.
			/**
			 * @brief Megpróbál magának egy kőoszlopot vagy vasércet keresni, amit aztán ki fog bányászni.
			 * 
			 * @param world A világ, amibe keresni kell az érceket.
			 */
			void try_mine(World& world);

		public:
			/**
			 * @brief Inicializál egy bányászt egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A bányász neme.
			 */
			Stonemason(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Stonemason(); ///< A bányász destruktora.
	};
}

#endif