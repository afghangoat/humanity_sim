/**
 * @file AnglerMiner.hpp
 * @brief Az "AnglerMiner" szakmájú ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef ANGLERMINER_HPP
#define ANGLERMINER_HPP

//#include "Human.h"
#include "Fisherman.h"
#include "Stonemason.h"

namespace creature{
	/**
	 * @class AnglerMiner
	 * @brief Az "AnglerMiner" szakmájú ember osztály leírása.
	 *
	 * Ez egy speciális szakma, ami tud követ és vasat bányászni és ha akar, még halászni is tud.
	 */
	class AnglerMiner: public Fisherman, public Stonemason{
		private:
			bool humanoid_run(float deltaTime) override; ///< Az emberszabású bányász-halász futás függvény.
			bool humanoid_walk(float deltaTime) override; ///< Az emberszabású bányász-halász mozgás függvény.
		public:
			/**
			 * @brief Inicializál egy AnglerMiner-t egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_modifier Az "AnglerMiner" neme.
			 */
			AnglerMiner(int x,int y,ENTITY_GENDER gender_modifier);
			
			void update_logic(World& world,float deltaTime) override;
			~AnglerMiner(); ///< Az AnglerMiner destruktora.
	};
}

#endif