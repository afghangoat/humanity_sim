/**
 * @file Shadowable.hpp
 * @brief Az árnyék szimulálásához való osztályt tartalmazza.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SHADOWABLE_HPP
#define SHADOWABLE_HPP

#include "TextureManager.h"
#include "GameConfig.h"

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif
#include <string>
#include <cmath>


/**
 * @class Shadowable
 * @brief Az árnyékoláshoz szükséges interface.
 *
 * Tárolja az árnyék textúráját, valamiért felelős annak mozgatásáért és rendes kirajzolásáért.
 */
class Shadowable {
	private:
		sf::Sprite shadow; ///< Az árnyék rajzolható felülete.
		sf::Vector2f originalShadowPos; ///< Az árnyék eredeti helye (Ez változik napszaktól függően).
		
		float inner_skew; ///< Az árnyék X tengelyen való nyújtási fázisa.
		int shadow_strength=150; ///< Az árnyék átlátszatlansága (0-255-ig).
		float skew_offset=0.01f; ///< Az árnyék nyújtásának mérete.
		
	protected:
		double height_offset=0.0; ///< Milyen messze kezdődjön az árnyék az objektum alsó pontjától.
	public:
		/**
		 * @brief Egy getter a magasságpont eltolásának megszerzésére.
		 * @return A magasságpont eltolásának értéke.
		 */
		double get_height_offset() const;
		/**
		 * @brief Egy getter az árnyék erősségre.
		 * @return Az árnyék erőssége.
		 */
		int get_shadow_strength() const;
		/**
		 * @brief Egy getter az elnyújtás mértékére.
		 * @return Az elnyújtás mértéke.
		 */
		float get_skew_offset() const;
		/**
		 * @brief Egy setter a magasságpont eltolásához.
		 * @param new_val Az új érték, amire be kell állítani.
		 */
		void set_height_offset(double new_val);
		/**
		 * @brief Egy setter az árnyék erősséghez.
		 * @param new_val Az új érték, amire be kell állítani.
		 */
		void set_shadow_strength(int new_val);
		/**
		 * @brief Egy setter a elnyújtás mértékéhez.
		 * @param new_val Az új érték, amire be kell állítani.
		 */
		void set_skew_offset(float new_val);
		
		virtual ~Shadowable() = default; ///< Virtuális destruktor.
		
		/**
		 * @brief Az árnyék kinézetét állítja be.
		 * @param filename A textúra elérési útvonala
		 * @return Igaz, ha sikeres a textúra beállítás, különben hamis.
		 */
		bool setShadowTexture(const std::string& filename);
		
		/**
		 * @brief Beállítja az árnyék nyújtását és eltolását.
		 * @param ySize Az Y tengelyen való nyújtás.
		 * @param xSkew Az X elnyújtás.
		 */
		void setShadow(float ySize, float xSkew);
		
		/**
		 * @brief Beállítja az árnyék nyújtását a napszaktól függően.
		 * @param delta_time Az előző frissítés óta eltelt idő.
		 */
		void setShadowDayNightCycle(float delta_time);
		
		/**
		 * @brief Beállítja az árnyék helyét.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		void setShadowPosition(double x, double y);
		
		/**
		 * @brief Kirajzolja az árnyékot.
		 * @param window Az ablak, ahova ki kell rajzolni.
		 */
		void drawShadow(sf::RenderWindow& window);
};
#endif