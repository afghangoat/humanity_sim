/**
 * @file Profession.hpp
 * @brief Ebben a fájlban van deklarálva a szakma indikátor osztály.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef PROFESSION_HPP
#define PROFESSION_HPP

#include "Textureable.h"
#include "TextureManager.h"
	
/*enum class PROFESSION_TYPE:char {
	KING,WOODCUTTER,EMPTY,FISHER,MINER,SHIPMAKER,SOLDIER,FARMER,BUILDER
};*/

/**
 * @class Profession
 * @brief A szakma osztály leírása.
 *
 * Tárolja a szakma ikonját és szimbólumát is.
 */
class Profession: public Textureable{
	private:
		sf::Sprite background_image; ///< Az ikon háttér borítója.
		sf::Sprite profession_image; ///< A szakma ikonja.
		
		std::string profession_string; ///< A szakma szimbóluma, ahogy a mentés fájlba megjelenik.
	public:
		/**
		 * @brief A konstruktor, ami egy szimbólum alapján betölti az ikon képet.
		 * @param intype A szakma szimbólum.
		 */
		Profession(const std::string& intype);
	
		bool setTexture(const std::string& filename) override;
		void setPosition(double x, double y) override;
		void draw(sf::RenderWindow& window) override;
		/**
		 * @brief Egy szimbólum alapján betölti az ikon képet.
		 * @param intype A szakma szimbólum.
		 */
		void load_profession(const std::string& new_profession);
		/**
		 * @brief Egy getter a szakma szimbólumához.
		 * @return A szakma szimbóluma szövegként.
		 */
		std::string to_string();
};
#endif