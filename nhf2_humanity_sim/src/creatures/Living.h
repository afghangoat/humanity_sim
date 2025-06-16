/**
 * @file Living.hpp
 * @brief Az élő interface itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef LIVING_HPP
#define LIVING_HPP

#include "../Textureable.h"
#include "../TextureManager.h"
#include "../GameConfig.h"
#include "../Shadowable.h"


#include <string>
#include <iostream>

#include "EntityBase.h"

class World;

/// @brief Az összes élőlény és entitás ebben a névtérben van.
namespace creature{

	/**
	 * @class Living
	 * @brief Az élő entitások interface leírása.
	 *
	 * Ebbe minden deklarálva van, amire egy entitásnak szüksége van.
	 * Tud fordulni, animált képet rajzolni, futni, mozogni, támadni, meghalni, "csinálni a dolgát".
	 * Eltárolja, hogy melyik entitás sebezte meg utoljára.
	 */
	class Living: public EntityBase, public Textureable, public Shadowable{
		private:
			
			sf::Sprite sprite; ///< Az entitás jelenlegi képe, amit ki kell rajzolni.
		protected:
			Living* damaged_by=nullptr; ///< Arra az entitásra pointer, ami utoljára megsebezte.
			
			static constexpr int MAX_CREATURE_SIZE=64;  ///< Mekkora a maximum entitás, amit még a kamera culling nélkül kirajzol, akkor is ha annak a középpontja nincs benne a látótérbe.
			
		public:
			void look_left(); ///< Balra nézeti az entitást.
			void look_right(); ///< Jobbra nézeti az entitást.
			/**
			 * @brief Ez a függvény jelzi, hogy megsebezték az entitást és azt, hogy ki sebezte meg.
			 * @param dam_by Az entitás, aki megsebezte.
			 * @param amm Mennyi sebzést kapott. Ezt levonja a metódus az entitás életéből.
			 */
			void damage(Living* dam_by,int amm);
			
			/**
			 * @brief Beállítja az entitás belső állapotát egy új értékre.
			 * @param newstate Az új belső állapot.
			 */
			void set_state(LIVINGSTATE newstate) override;
			
			/**
			 * @brief Beállítja az entitásnak azt, hogy hány képkockás animációja legyen és az milyen gyors legyen.
			 * @param maxframes A képkockák száma.
			 * @param animspeed Az animáció gyorsasága.
			 */
			void init_spritesheet_data(int maxframes, double animspeed);
		
			bool setTexture(const std::string& filename) override;
			/**
			 * @brief Beállítja az entitás árnyék textúráját.
			 * @param filename Az árnyék textúra elérési útvonala.
			 */
			bool setTheShadow(const std::string& filename);
			void setPosition(double x, double y) override; ///< Beállítja, hogy hova kell kirajzolni az entitást.
			/**
			 * @brief Frissíti az entitás animációját az idő függvényében.
			 * @param deltaTime Az előző frissítés óta eltelt idő.
			 */
			void update_spritesheet(float deltaTime);
			/**
			 * @brief Kirajzolja az élő entitást a render screen-re.
			 * @param window A render ablak.
			 */
			void draw(sf::RenderWindow& window) override;
			
			/**
			 * @brief Megnézi, hogy a felhasználó látja-e az entitást.
			 * @return Benne van-e a látótérbe.
			 */
			bool needs_drawn();
			
			/**
			 * @brief Visszaadja az entitás vastagságát.
			 * @return Az entitás vastagsága.
			 */
			int get_width() const;
			
			/**
			 * @brief Visszaadja, hogy kire "ideges az entitás". Ez lehet az, hogy ki ütötte meg vagy hogy kit akar megenni.
			 * @return Az entitás, akire ideges. Nullpointer, ha nincs ilyen entitás.
			 */
			virtual Living* check_aggroed() const;
			/**
			 * @brief Felidegesíti az entitást a kapott entitásra.
			 * @param new_target Az entitás, akire dühösnek kell lennie.
			 */
			virtual void retarget(Living* new_target);
			
			/**
			 * @brief Az entitás frissítési logikája itt van definiálva. Példáúl a halász vizet keres, ha odaért akkor halászik.
			 * @param world A világ, amibe frissíti magát az entitás.
			 * @param deltaTime Az előző frissítés óta eltelt idő.
			 */
			virtual void update_logic(World& world,float deltaTime)=0;
			/**
			 * @brief Az entitás kirajzolás logikája, példáúl az ember az árnyékát és képét rajzolja ki, de a robot csak a képét.
			 * @param window Az ablak, ahova rajzolni kell.
			 * @param deltaTime Az előző frissítés óta eltelt idő.
			 * @param offx A kamera X eltolása.
			 * @param offy A kamera Y eltolása.
			 */
			virtual void draw_logic(sf::RenderWindow& window,float deltaTime,int offx,int offy)=0;
			/**
			 * @brief Az entitás árnyékolás logikája, itt állítódik be az árnyék fázisa.
			 * @param window Az ablak, ahova rajzolni kell.
			 * @param elapsed_time A szimuláció kezdete óta eltelt idő.
			 * @param offx A kamera X eltolása.
			 * @param offy A kamera Y eltolása.
			 */
			void shadow_logic(sf::RenderWindow& window, float elapsed_time,int offx,int offy);
			
			virtual ~Living(); ///< Virtuális destruktor.
	};
}

#endif