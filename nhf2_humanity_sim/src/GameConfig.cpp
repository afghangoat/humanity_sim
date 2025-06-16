#include "GameConfig.h"

GameConfig::GameConfig(){}

GameConfig& GameConfig::get_instance() {
    static GameConfig instance;
    return instance;
}

int GameConfig::get_config_level() const {
    return debug_level;
}

int GameConfig::get_target_fps() const {
	return target_fps;
}

void GameConfig::set_config_level(int n_flag){
	
	std::lock_guard<std::mutex> lock(mtx);
	
	if(n_flag<0){
		if(what_language==Language::MAGYAR){
			std::cerr << "Helytelen konfig szint beállítási kérés érkezett: " << n_flag << std::endl;
		} else if(what_language==Language::ENGLISH){
			std::cerr << "Tried to set config level to invalid state: " << n_flag << std::endl;
		}
	} else {
		debug_level=n_flag;
	}            
}

int GameConfig::get_screen_width() const{
	return screen_width;
}

int GameConfig::get_screen_height() const{
	return screen_height;
}

int GameConfig::get_world_size() const{
	return world_size;
}
void GameConfig::set_world_size(int newsize){
	if(newsize<1){
		world_size=newsize;
	}
}

Language GameConfig::get_lang() const{
	return what_language;
}
Language GameConfig::get_sfml_lang() const{
	return what_sfml_language;
}

int GameConfig::get_max_spawn_tries() const{
	return max_spawn_tries;
}
int GameConfig::get_resource_scarcity() const{
	return resource_scarcity;
}
int GameConfig::get_hostiles_count() const{
	return hostiles_count;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos){
		return "";
	}
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

bool GameConfig::read_from_config_file(const std::string& filepath){
	YAMLParser parser;
	bool is_fresh_config=parser.try_generate_config_file(filepath);
	if(is_fresh_config==true){
		if(what_language==Language::MAGYAR){
			std::cerr << "Friss konfigurációs fájl létrehozva ezzel a névvel: " << filepath << std::endl;
		} else if(what_language==Language::ENGLISH){
			std::cerr << "Fresh config file created with name: " << filepath << std::endl;
		}
	}
	
	bool success=parser.parse_file(filepath);
	if(success==false){
		return false;
	}
	
	set_config_level(std::stoi(parser.get_value_of_key("debug_level")));
	set_world_size(std::stoi(parser.get_value_of_key("world_size")));
	target_fps=std::stoi(parser.get_value_of_key("target_fps"));
	screen_height=std::stoi(parser.get_value_of_key("screen_height"));
	screen_width=std::stoi(parser.get_value_of_key("screen_width"));
	
	std::string config_lang=trim(parser.get_value_of_key("what_language"));
	if(config_lang=="ENGLISH"){
		what_language=Language::ENGLISH;
	} else if(config_lang=="MAGYAR"){
		what_language=Language::MAGYAR;
	} else {
		what_language=Language::NONE;
	}
	std::string sfml_lang=trim(parser.get_value_of_key("what_sfml_language"));
	if(sfml_lang=="ENGLISH"){
		what_sfml_language=Language::ENGLISH;
	} else if(sfml_lang=="MAGYAR"){
		what_sfml_language=Language::MAGYAR;
	} else {
		what_sfml_language=Language::NONE;
	}
	
	max_spawn_tries=std::stoi(parser.get_value_of_key("max_spawn_tries"));
	hostiles_count=std::stoi(parser.get_value_of_key("hostiles_count"));
	resource_scarcity=std::stoi(parser.get_value_of_key("resource_scarcity"));
	day_length=std::stof(parser.get_value_of_key("day_length"));
	int noise_entry=std::stof(parser.get_value_of_key("noise"));
	noise= (noise_entry == 1) ? true : false;
	int aberration_entry=std::stof(parser.get_value_of_key("chromatic_aberration"));
	chromatic_aberration= (aberration_entry == 1) ? true : false;
	
	return true;
}

bool GameConfig::is_noise() const{
	return noise;
}
bool GameConfig::is_chromatic_aberration() const{
	return chromatic_aberration;
}