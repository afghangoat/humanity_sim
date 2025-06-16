/**
 * @file Goat.hpp
 * @brief A Kecske osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef GOAT_HPP
#define GOAT_HPP

#include "Living.h"
#include "../Random_Gen.h"
#include "../Utils.h"

namespace creature{
	
	/**
	 * @class Goat
	 * @brief A kecske osztály leírása.
	 *
	 * A kecske egy passzív, nem támadó állat, amit ha az emberek megölnek, ételt ad.
	 */
	class Goat: public Living{
		private:
			sf::Vector2f goal; ///< A kecske célpontja.
			
			bool goat_idle(World& world); ///< A kecske semmit nem csinálás függvénye.
			bool goat_run(float deltaTime); ///< A kecske futás animációja.
			bool goat_walk(float deltaTime); ///< A kecske mozgás függvénye.
			
		public:
			/**
			 * @brief Idéz egy kecskét egy pontos x és y coordinátára és beállítja az attribútumait.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			Goat(int x,int y);
			ENTITY_TYPE get_type() const override;
			
			void die() override;
			void update_logic(World& world,float deltaTime) override;
			void draw_logic(sf::RenderWindow& window,float deltaTime,int offx, int offy) override;
			virtual ~Goat(); ///< Virtuális destruktor.
	};
}

#endif