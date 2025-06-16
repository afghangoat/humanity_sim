/**
 * @file PostProcesser.hpp
 * @brief A grafikus szépítő osztály deklarációját tartalmazza.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef POSTPROCESS_HPP
#define POSTPROCESS_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif
#include <string>
#include "TextureManager.h"

/**
 * @class PostProcesser
 * @brief A grafikus szépítő osztály leírása.
 *
 * Különböző szépítések beállíthatóak: Zaj, Szín, Chromatic aberration, Vignette.
 */
class PostProcesser{
	private:
		sf::Sprite vignette_sprite; ///< A vignetta kép, amit majd kirajzol az osztály.
		sf::RectangleShape colorRect; ///< A szín, amit majd kirajzol az osztály.
		sf::Sprite noise_sprite; ///< A zaj kép, amit majd kirajzol az osztály.
		sf::Sprite chromatic_aberration_sprite; ///< A Chromatic aberration kép, amit majd kirajzol az osztály.
		
		bool vignette_enabled; ///< Rajzoljon-e az osztály vignettát.
		bool overlay_enabled; ///< Rajzoljon-e az osztály szín réteget.
		bool noise_enabled; ///< Rajzoljon-e az osztály zajt.
		bool chromatic_aberration_enabled; ///< Rajzoljon-e az osztály Chromatic aberration-t.
		
	public:
		PostProcesser(); ///< A konstruktor, a használt textúrák betöltése itt történik.
		
		/**
		 * @brief Ki-be kapcsolja a vignettát.
		 * @param newval Ha igaz, akkor ezen túl ki lesz rajzolva, különben nem lesz.
		 */
		void toggle_vignette(bool newval);
		/**
		 * @brief Ki-be kapcsolja a zajt.
		 * @param newval Ha igaz, akkor ezen túl ki lesz rajzolva, különben nem lesz.
		 */
		void toggle_noise(bool newval);
		/**
		 * @brief Ki-be kapcsolja a Chromatic aberration-t.
		 * @param newval Ha igaz, akkor ezen túl ki lesz rajzolva, különben nem lesz.
		 */
		void toggle_chromatic_aberration(bool newval);
	
		/**
		 * @brief Beállít egy képnek egy új textúrát.
		 * @param what Azt a képet, amit be kell állítani.
		 * @param filename Az új textúra elérési útvonala.
		 * @return Sikerült-e.
		 */
		bool setTextureFor(sf::Sprite& what,const std::string& filename);
		/**
		 * @brief Beállítja azt a négyzetet (0,0) (x,y)-ig, ahol a szépítő osztály dolgozni fog.
		 * @param x A szélesség.
		 * @param y A magasság.
		 */
		void setRenderSize(double x, double y);
		/**
		 * @brief Kirajzolódik az osztály.
		 * @param window Az ablak, amire rajzolódik.
		 */
		void draw(sf::RenderWindow& window);
		/**
		 * @brief Beállítja az új szín réteget.
		 * @param r Piros komponens.
		 * @param g Zöld komponens.
		 * @param b Kék komponens.
		 * @param a Alfa komponens.
		 */
		void setColorOverlay(int r, int g, int b, int a);
};
#endif