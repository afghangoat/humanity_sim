#ifndef ENTITY_UTILS_HPP
#define ENTITY_UTILS_HPP

#include <string>
#include <iostream>
#include "../GameConfig.h"

namespace creature{
	
	enum class ENTITY_TYPE:char {
		HUMAN,ANIMAL,ROBOTIC
	};
	enum class ENTITY_GENDER:char {
		MALE,FEMALE
	};
	enum class FACING:bool {
		RIGHT,LEFT
	};
	enum class LIVINGSTATE:int {
		IDLE,RUN,WALK,DEATH,ATTACKING,DOING_ITS_WORK
	};

	/**
	 * @class LivingTexture
	 * @brief Az élő entiások kinézetének adatai.
	 *
	 */
	struct LivingTexture{
		public:
			std::string idle_texture_path; ///< Az entitás semmit nem csinálás képének az elérési útvonala.
			std::string attack_texture_path; ///< Az entitás támadás képének az elérési útvonala.
			std::string walk_texture_path;  ///< Az entitás sétálás képének az elérési útvonala.
			std::string run_texture_path;  ///< Az entitás futás képének az elérési útvonala.
			std::string death_texture;  ///< Az entitás meghalás képének az elérési útvonala.
			
			int frame_count; ///< Hány képkockából áll egy animáció.
			double animation_speed; ///< Milyen gyorsan változzon az animáció.
			double current_animation_time; ///< A jelenlegi animáció időt tárolja és ez alapján választja ki a kirajzolt képkockát.
	};
}

#endif