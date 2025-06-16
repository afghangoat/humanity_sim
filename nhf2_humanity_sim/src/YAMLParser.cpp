#include "YAMLParser.h"

#include "GameConfig.h"
#include "Utils.h"
#include <filesystem>

const std::string YAMLParser::delimiter = ":";
const std::string YAMLParser::invalid_symbol = "INVALID";
YAMLParser::YAMLParser(){
	read_in=false;
}

bool YAMLParser::parse_file(const std::string& filepath){
	if(read_in==true){
		current_file_content.clear();
	}
	
	std::string temp_text;
	std::ifstream YAML_parse(filepath);
	if (!YAML_parse.is_open()) {
		warn_text(
			"A YAML beolvasó nem tudta megnyitni ezt a fájlt: " + filepath,
			"The YAML loader failed to open this file: " + filepath,
			2
		);
		return false;
	}

	while (std::getline(YAML_parse, temp_text)) {
		
		temp_text.erase(std::remove(temp_text.begin(), temp_text.end(), '\t'), temp_text.end());
		temp_text.erase(std::remove(temp_text.begin(), temp_text.end(), ' '), temp_text.end());
		if(temp_text[0]!='#'&&temp_text.size()>1){
			
			std::string token1 = temp_text.substr(0, temp_text.find(delimiter));
			std::string token2 = temp_text.substr(temp_text.find(delimiter)+1, temp_text.size()-1);
			
			current_file_content[token1]=token2;
		}
	}
	
	YAML_parse.close();
	
	read_in=true;
	return true;
}

std::string YAMLParser::get_value_of_key(const std::string& key) const{
	auto it = current_file_content.find(key);
	return it != current_file_content.end() ? it->second : invalid_symbol;
}

bool YAMLParser::try_generate_config_file(const std::string& filename) {
    namespace fs = std::filesystem;

    if (fs::exists(filename)) {
        return false;
    }

    fs::path filepath(filename);
    if (!filepath.parent_path().empty()) {
		fs::create_directories(filepath.parent_path());
	}

    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }

    out <<
	R"(#Mennyire legyen bőbeszédű a program debug loggere? (0: csak kritikus, 1: hibák, 2: figyelmeztetés, 3: minden)
debug_level: 3
#Mennyi legyen a megcélzott fps?
target_fps: 60

#A render ablak mérete:
screen_width: 960
screen_height: 640

#Hányszor hány kocka legyen a világ.
world_size: 40

#Milyen nyelvű legyen a logger: (NONE: ne logoljon, MAGYAR: Magyarul, ENGLISH: Angolul)
what_language: MAGYAR
#Milyen nyelvű legyen az SFML logger: (NONE: ne logoljon, MAGYAR: Magyarul, ENGLISH: Angolul)
what_sfml_language: NONE

max_spawn_tries: 99

hostiles_count: 1
resource_scarcity: 4

day_length: 400.0

#Egyéb grafikus beállítások
chromatic_aberration: 0
noise: 0
)";

    out.close();
    return true;
}