/**
 * @file Utils.hpp
 * @brief Ebben a fájlba vannak a segéd függvények.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#ifndef FAKE_SFML
	#define WITH_SFML_RENDER ///< Ez arra kell, ha nem headless mode kell a programból.
#endif

#include <cmath>
#include <string>

/**
 * @brief Visszaadja a távolságot az (x1,y1) (x2,y2) pont között.
 * @param x1 Az 1. pont x koordinátája.
 * @param y1 Az 1. pont y koordinátája.
 * @param x2 Az 2. pont x koordinátája.
 * @param y2 Az 2. pont y koordinátája.
 * @return A távolság a 2 pont között.
 * @warning Ez a függvény jelenleg nincs használatban.
 */
double distance_to(double x1, double y1, double x2, double y2);

void log_text(const std::string& english, const std::string& magyar); ///< Könnyebb tesztelést biztosít, ha az SFML magyarúl írja ki, mit csinált. Van angol nyelvre is lehetőség és arra is, hogy ne írjon semmit.
void warn_text(const std::string& english, const std::string& magyar, int config_minimum); ///< Könnyebb tesztelést biztosít, a program magyarúl írja ki, mit csinál. Van angol nyelvre is lehetőség és arra is, hogy ne írjon semmit.

#endif