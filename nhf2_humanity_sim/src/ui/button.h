/**
 * @file button.hpp
 * @brief A gomb osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Textureable.h"
#include "../TextureManager.h"
#include <iostream>
#include <functional>
#include <string>


/// @brief Az összes UI elem ebben a névtérben van.
namespace ui{
	/**
	 * @class Button
	 * @brief A gomb osztály leírása. Tárolja a gomb méretét és azt, hogy mit csinál, ha rákattintanak.
	 */
	class Button: public Textureable {
		private:
			int x; ///< A gomb X koordinátája.
			int y; ///< A gomb Y koordinátája.
			int width; ///< A gomb szélessége.
			int height; ///< A gomb magassága.
			std::function<void()> callback; ///< Milyen függvény hajtódjon végre, ha rákattintanak.
			bool clicked; ///< Kattintottak-e a gombra.
			bool hovered; ///< Rajta van-e a kurzor a gombon.
			sf::Sprite sprite;  ///< A gomb képe.
			
			sf::RenderStates states;  ///< Segéd adattag a gomb animációjához.

		public:
			/**
			 * @brief A konstruktor ami létrehozza a gombot megadott mérettel és képpel.
			 * @param px A gomb X koordinátája.
			 * @param py A gomb Y koordinátája.
			 * @param width A gomb szélessége.
			 * @param height A gomb magassága.
			 * @param spritepath A gomb képének elérési útvonala.
			 */
			Button(int px, int py, int width, int height,const std::string& spritepath);
			
			/**
			 * @brief Beállítja, mi történjen, ha a gombra kattintanak.
			 * @param func A függvény, ami le fog futni.
			 */
			void setCallback(std::function<void()> func);

			/**
			 * @brief Megnézi, hogy az egér kurzor rajta van-e a gombon.
			 * @param mX A kurzor X koordinátája.
			 * @param mY A kurzor Y koordinátája.
			 */
			void try_hover_animation(int mX, int mY);
			
			/**
			 * @brief Megnézi, hogy kattintottak-e rá, ha igen akkor végrehajta a függvényt amit neki adtak be.
			 * @param mc Le van-e nyomva az egér gomb.
			 */
			void onClick(bool mc);

			bool setTexture(const std::string& filename) override;
			void setPosition(double x, double y) override;
			void draw(sf::RenderWindow& window) override;
	};
}


#endif