/**
 * @file Fisherman.hpp
 * @brief A halász szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef FISHERMAN_HPP
#define FISHERMAN_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Fisherman
	 * @brief A halász szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember víz terepkockát keres és ott halászva ételt szerez.
	 */
	class Fisherman: virtual public Human{
		protected:
			bool fishing; ///< Halászni akar-e az ember jelenleg?
			/**
			 * @brief Megpróbál tavat keresni, ahol halászhat.
			 * 
			 * @param world A világ, amibe tavat kell keresni.
			 */
			void try_fishing(World& world);
		
		public:
			/**
			 * @brief Inicializál egy halászt egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A halász neme.
			 */
			Fisherman(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Fisherman(); ///< A halász destruktora.
	};
}

#endif