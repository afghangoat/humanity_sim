/**
 * @file Tile.hpp
 * @brief A Terepkocka osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "../Textureable.h"
#include "../TextureManager.h"

/// @brief Az összes terepkocka elem ebben a névtérben van.
namespace tiles{
	
	enum class TILETYPE:char {
		GRASS,WATER,MOUNTAIN
	};
	/**
	 * @class Tile
	 * @brief A terepkocka osztály leírása.
	 *
	 * Tárolja a terepkocka kinézetét és azt, hogy milyen biom típusú.
	 */
	class Tile: public Textureable{
		private:
			sf::Sprite sprite; ///< A terepkocka kinézete.
			TILETYPE inner_type; ///< A terepkocka biotípusa.
			
		public:
			/**
			 * @brief Inicializálja a terepkocka kinézetét a biotípusa alapján.
			 * @param newtype A biotípusa.
			 */
			void init(TILETYPE newtype);
			/**
			 * @brief Egy getter ami visszaadja a terepkocka biotípusát.
			 * @return A biotípusa.
			 */
			TILETYPE get_type() const;
		
			bool setTexture(const std::string& filename) override;
			void setPosition(double x, double y) override;
			void draw(sf::RenderWindow& window) override;
			
	};
}

#endif