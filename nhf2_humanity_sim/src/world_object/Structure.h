/**
 * @file Structure.hpp
 * @brief A struktúra osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef STRUCTUREA_HPP
#define STRUCTUREA_HPP

#include "../Textureable.h"
#include "../TextureManager.h"
#include "../GameConfig.h"
#include "../Shadowable.h"

#include <string>
#include <iostream>

/// @brief Az összes struktúra ebben a névtérben van.
namespace minerals{
	
	enum class MINERAL_TYPE:char {
		STONE,WOOD,IRON,FOOD,HOUSING,CITY_CENTER
	};

	/**
	 * @class Structure
	 * @brief A struktúra osztály leírása.
	 *
	 * A Textúrázható és Árnyékolható interface-ből öröklődik.
	 * Alaposztály amiből később jönnek a házak, erőforrások.
	 */
	class Structure: public Textureable, public Shadowable{
		private:
			sf::Sprite sprite; ///< A kinézete a struktúrának.
		protected:
			const int MAX_OBJECT_SIZE=64; ///< Egy határ, minnél nagyobb, annál nagyobb környezetbe lesznek kirajzolva a nézőpontból.
		public:
			int posx; ///< Az X koordináta, amin elhelyezkedik.
			int posy; ///< Az Y koordináta, amin elhelyezkedik.
			
			/**
			 * @brief Létrehozza magát az x és y megadott pontban.
			 * @param x Az x koordináta.
			 * @param y Az y koordináta.
			 */
			Structure(int x, int y);
		
			bool setTexture(const std::string& filename) override;
			void setPosition(double x, double y) override;
			void draw(sf::RenderWindow& window) override;
			
			bool needs_drawn(); ///< Igazat ad vissza, ha látható és ezért ki kell rajzolni.
			
			virtual MINERAL_TYPE get_type() const=0; ///< Szimbólum, ami a fájlba mentéshez kell.
			
			/**
			 * @brief Frissíti magát az idő függvényében.
			 * @param deltaTime Az előző frissités óta eltelt idő.
			 */
			virtual void update_logic(float deltaTime)=0;
			
			/**
			 * @brief Kirajzolja a struktúrát attól függően, hogy ki kell-e.
			 * @param window Az ablak, ahova rajzolni kell.
			 * @param elapsed_time A világ megléte óta eltelt idő.
			 * @param offx A kamera X eltolása.
			 * @param offy A kamera Y eltolása.
			 */
			void draw_logic(sf::RenderWindow& window,float elapsed_time,int offx,int offy);
			
			virtual ~Structure()=default; ///< Alap virtuális destruktor.
			
	};
}

#endif