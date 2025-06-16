#include "EntityBase.h"
#include "../exceptions/FileExceptions.h"

//FOR EntityBase
namespace creature{
	void EntityBase::set_health(int amm){
		health=amm;
	}
	
	ENTITY_GENDER EntityBase::get_gender() const{
		return gender;
	}
	LIVINGSTATE EntityBase::get_state() const{
		return state;
	}
	EntityBase::~EntityBase(){
		
	}
	void EntityBase::apply_age(){
		if(inner_timer>=max_age){
			set_state(LIVINGSTATE::DEATH);
		}
	}
	
	void EntityBase::set_idle_texture(std::string new_str){
		if(new_str!=""){
			texture_data.idle_texture_path=new_str;
		} else {
			warn_text(
				"Failed to load idle texture, got empty string",
				"Nem sikerült betölteni a tétlen textúrát, üres karakterláncot kaptunk",
				0
			);
		}
	}
	
	void EntityBase::set_attack_texture(std::string new_str){
		if(new_str!=""){
			texture_data.attack_texture_path=new_str;
		} else {
			warn_text(
				"Failed to load attack texture, got empty string",
				"Nem sikerült betölteni az attack textúrát, üres karakterláncot kaptunk",
				0
			);
		}
	}
	void EntityBase::set_walk_texture(std::string new_str){
		if(new_str!=""){
			texture_data.walk_texture_path=new_str;
		} else {
			warn_text(
				"Failed to load walk texture, got empty string",
				"Nem sikerült betölteni a séta textúrát, üres karakterláncot kaptunk",
				0
			);
		}
	}
	void EntityBase::set_run_texture(std::string new_str){
		if(new_str!=""){
			texture_data.run_texture_path=new_str;
		} else {
			warn_text(
				"Failed to load run texture, got empty string",
				"Nem sikerült betölteni a futás textúrát, üres karakterláncot kaptunk",
				0
			);
		}
	}
	void EntityBase::set_death_texture(std::string new_str){
		if(new_str!=""){
			texture_data.death_texture=new_str;
		} else {
			warn_text(
				"Failed to load death texture, got empty string",
				"Nem sikerült betölteni a halál textúrát, üres karakterláncot kaptunk",
				0
			);
		}
	}
	float EntityBase::get_death_timer() const{
		return death_timer;
	}
	const std::string& EntityBase::get_save_name() const{
		return save_name;
	}
	
	void EntityBase::set_save_name(const std::string& s){
		if(s==""){
			throw ImportInvalidHumanProfessionException("Nem lehet egy objektum fájl szimbóluma üres.");
		}
		save_name=s;
	}
}