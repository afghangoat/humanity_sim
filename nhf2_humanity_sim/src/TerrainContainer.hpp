/**
 * @file TerrainContainer.hpp
 * @brief A Világ terepének a deklarálása ebben a fájlba van.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */

#ifndef DYN_2D_HPP
#define DYN_2D_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif
#include "GameManager.h"
#include "GameConfig.h"
#include "Random_Gen.h"
#include "terrain_tiles/Tile.h"

/**
 * @class TerrainContainer
 * @brief A világ terepét tároló osztály
 * @tparam T A generikus elem, amiket eltárol ez a konténer.
 *
 * Egy dinamikus 2 dimenziós n*m-es tömb. Rendelkezik a szükséges getterekkel.
 * Ez az osztály felelős a világ terepének a véletlen generálásáért is.
 */
template <typename T>
class TerrainContainer {
	private:
		T** in_array = nullptr; ///< A dinamikus elemek tárolásához szükséges pointer.
		int width = 0; ///< A tömb szélessége.
		int height = 0; ///< A tömb magassága.
		
		int seed=-1; ///< A véletlen generáláskor használt seed. Ha ez -1 akkor véletlen érték lesz. Ha nem, akkor a beállított értéket használja.

	public:
		/**
		* @brief Egy getter a tömb szélességére.
		* @return A tömb szélessége.
		*/
		int get_width() const;
		/**
		* @brief Egy getter a tömb magasságára.
		* @return A tömb magassága.
		*/
		int get_height() const;
		
		const int TILE_SIZE=32; ///< Egy terep maximális textúra mérete. Ennél nagyobb terepkockák talán nem rajzolódnak ki, mert a kamera úgy érzékeli, hogy már nincs bennt a látótérben.
		
		TerrainContainer(); ///< Alapkonstruktor. Nem történik memória foglalás.
		
		/**
		* @brief Konstruktor, ami már foglal memóriát és generál terepet.
		* @param awidth Az új szélesség.
		* @param aheight Az új magasság.
		* @param def_value Alap érték, amivel feltöltődik a tömb.
		*/
		TerrainContainer(int awidth, int aheight, T def_value);
		
		/**
		* @brief Kicseréli a (x1,y1) kockát az (x2,y2) helyen lévő kockával.
		* @param x1 Az 1. kocka x koordinátája.
		* @param y1 Az 1. kocka y koordinátája.
		* @param x2 A 2. kocka x koordinátája.
		* @param y2 A 2. kocka y koordinátája.
		*/
		void swap_at(int x1, int y1, int x2, int y2);
		
		/**
		 * @brief Visszaadja, hogy az (x,y) koordinátán lévő terepkocka helyesen van definiálva-e.
		 * @param x Oszlop index.
		 * @param y Sor index.
		 * @return Igaz, ha rendesen van definiálva és már használható, különben hamis.
		 */
		bool is_valid_coordinate(int x, int y);
		
		/**
		 * @brief Visszaadja, hogy az (x,y) koordinátán lévő terepkocka rajta van-e a látható síkon.
		 * @param x Oszlop index.
		 * @param y Sor index.
		 * @return Igaz, rajta van, különben hamis.
		 */
		bool is_on_screen(int x, int y);
		
		T*& operator[](std::size_t row); ///< operator[] hogy elérhetőek legyenek a belső elemek.
		T* const& operator[](std::size_t row) const; ///< konstans operator[] hogy elérhetőek legyenek a belső elemek.
		
		/**
		 * @brief Kirajzolja az (x,y) koordinátán lévő terepkockát.
		 * @param window Ahova ki kell rajzolni a terepkockát.
		 * @param x Oszlop index.
		 * @param y Sor index.
		 */
		void draw(sf::RenderWindow& window, int offx, int offy);
		void generate_world(); ///< Generál egy új terepet.
		
		/**
		 * @brief Felszabadítja az adott sorban és oszlopban elhelyezkedő terepkockát.
		 * @param x Oszlop index.
		 * @param y Sor index.
		 */
		void clear_at(int x, int y);
		void clear(); ///< Felszabadítja a tárolt terepkockákat.
		
		/**
		 * @brief Setter, beállítja a seedet az új megadott értékre.
		 * @param new_value Az új érték.
		 */
		void set_seed(int new_value);
		/**
		 * @brief Getter, visszaadja a seedet.
		 * @return A seed.
		 */
		int get_seed() const;
		
		/**
		 * @brief Újraméretezi a terepet az új méreteir és feltölti a megadott típusú adattal.
		 * @tparam Defvalue Az érték amivel az új terep fel lesz töltve.
		 * @param awidth Az új érték.
		 * @param aheight Az új érték.
		 */
		template<typename Defvalue>
		void resize(int awidth, int aheight);
		
		~TerrainContainer(); ///< A destruktor, ami kitörli az összes tárolt terepkockát a clear() meghívásával.
};

#include "TerrainContainer_def.hpp"

#endif
