/**
 * @file Textureable.hpp
 * @brief Ebbe a fájlba van a textúrázáshoz szükséges osztály.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */

#ifndef TEXTUREABLE_HPP
#define TEXTUREABLE_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif
#include <string>

/**
 * @class Textureable
 * @brief Egy interface, ami a textúrázáshoz kell.
 *
 * Jelzi, hogy a kirajzolásához és a világban való megjelenítéséhez milyen metódusokat kell elkészíteni.
 */
class Textureable {
	public:
		virtual ~Textureable() = default; ///< Alap virtuális destruktor.
		
		/**
		 * @brief Beállít egy fájl elérési útból egy textúrát. Megvalósítástól függően esetleg 2-t.
		 * @param filename A textúra elérési útja.
		 * @return Sikeres volt-e a textúra beállítása.
		 */
		virtual bool setTexture(const std::string& filename) = 0;
		
		/**
		 * @brief Beállítja, hogy hova kell rajzolni a textúrázható leszármozottat.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		virtual void setPosition(double x, double y) = 0;
		
		/**
		 * @brief Kirajzolja az objektumot.
		 * @param window Ahova ki kell rajzolni a textúrázható leszármozottat.
		 */
		virtual void draw(sf::RenderWindow& window) = 0;
};
#endif