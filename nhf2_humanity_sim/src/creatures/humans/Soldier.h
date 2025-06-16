/**
 * @file Soldier.hpp
 * @brief A katona szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Human.h"

namespace creature{
	/**
	 * @class Soldier
	 * @brief A katona szakmájú ember osztály leírása.
	 *
	 * Ez a szakmájú ember vadászik állatokat és megvédi a népet az ellenséges entitásoktól.
	 */
	class Soldier: public Human{
		private:
			Living* target; ///< A katona célpontja
			int damage; ///< A katona sebzése.
			float attack_speed; ///< A katona támadási sebessége.
			
			bool humanoid_run(float deltaTime) override; ///< Az emberszabású katona futás függvény.
			bool humanoid_walk(float deltaTime) override; ///< Az emberszabású katona mozgás függvény.
			
			void attacking(); ///< A katona támadását végrehajtó metódus.
		public:
			/**
			 * @brief Inicializál egy katonát egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier A katona neme.
			 */
			Soldier(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~Soldier(); ///< A katona destruktora.
			
			
	};
}

#endif