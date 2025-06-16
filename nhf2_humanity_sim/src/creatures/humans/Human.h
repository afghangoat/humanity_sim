/**
 * @file Human.hpp
 * @brief Az alap ember osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "../Living.h"
#include "../../Random_Gen.h"
#include "../../Profession.h"
#include "../../world_object/CityCenter.h"
#include "../../Utils.h"

namespace creature{
	/**
	 * @class Human
	 * @brief Az alap ember osztály leírása. Minden fajta szakmájú ember innen öröklődik.
	 *
	 * Tárolja az ember szakma címerét, célkoordinátáját is.
	 */
	class Human: public Living{
		protected:
			Profession* profession=nullptr; ///< A szakma ikon pointere.
			sf::Vector2f goal; ///< A cselekvésének a célpontja.
			
			virtual bool humanoid_run(float deltaTime); ///< Az emberszabású futás függvény.
			virtual bool humanoid_walk(float deltaTime); ///< Az emberszabású mozgás függvény.
			
		public:
			bool needs_to_be_royal; ///< Kell-e királyá koronázni?
			bool needs_promotion; ///< Kell-e neki egy új szakma? Csak akkor igaz, ha már van város.
			
			/**
			 * @brief Az alap konstruktor ami leidézi az embert egy x és y coordinátára.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			Human(int x,int y);
			/**
			 * @brief Az alap konstruktor ami leidézi az embert egy x és y coordinátára egy megadott nemmel.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param const_gender Az ember neme.
			 */
			Human(int x,int y, ENTITY_GENDER const_gender);
			ENTITY_TYPE get_type() const override;
			
			void die() override;
			void update_logic(World& world,float deltaTime) override;
			void draw_logic(sf::RenderWindow& window,float deltaTime,int offx, int offy) override;
			virtual ~Human(); ///< Virtuális destruktor, felszabadítja a szakma ikon pointert is.
			
			/**
			 * @brief Beállítja az ember tulajodnságait: életpontok, max életkor, nem.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			void initialize(int x,int y);
			/**
			 * @brief Beállít egy textúrát ami nagyon különböző lehet emberenéknt és egyből beállítja, hogy az embert a saját (x,y) koordinátára rajzolják.
			 * 
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 * @param gender_selector Egy véletlen szám. Ettől függ a textúra variáció.
			 */
			void select_texture(int x, int y,int gender_selector);
			
			/**
			 * @brief Lekérhető az ember szakmájának szöveggé alakított szimbóluma. Ez fontos a fájlba tároláshoz.
			 * 
			 * @return Az ember szakmájának szimbóluma.
			 */
			std::string get_profession_string();
	};
}

#endif