/**
 * @file Random_Gen.hpp
 * @brief A véletlen generátor osztályt tároló fájl.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef RND_GEN_HPP
#define RND_GEN_HPP

#include <iostream>
#include <chrono>
#include <random>
#include <mutex>

/**
 * @class RandomGenerator
 * @brief Egy korszerűbb és konfigurálhatóbb véletlen szám generátor osztály.
 *
 * Singleton pattern-t használ.
 */
class RandomGenerator {
	private:
		std::random_device rd; ///< A véletlen generátor.
		std::mt19937 gen; ///< A véletlen generátor hash algoritmus.
		std::mutex mtx; ///< Mutex. Segíti, hogy párhuzamosított környezetben is működjön az osztály funkciója.

		RandomGenerator() : gen(rd() ^ ((std::mt19937::result_type) std::chrono::duration_cast<std::chrono::seconds>( std::chrono::system_clock::now().time_since_epoch() ).count() + (std::mt19937::result_type) std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() ).count())) {} ///< Privát konstruktor, ami beállítja a véletlen generátor algoritmust az idő függvényébe.

	public:
		RandomGenerator(const RandomGenerator&) = delete; ///< A singleton pattern miatt törölve.
		
		RandomGenerator& operator=(const RandomGenerator&) = delete; ///< A singleton pattern miatt törölve.

		/**
		 * @brief Visszaad egy referenciát erre az osztály-ra.
		 * @return A singleton-hoz egy referencia.
		 * @static
		 */
		static RandomGenerator& get_instance();

		/**
		 * @brief 0 és a max-1 számok között visszaad egy véletlen számot.
		 * @param max A maximum érték, aminél már csak kisebb számokat ad vissza.
		 * @return A határ mérete.
		 */
		int get_random_int(int max);
};

#endif