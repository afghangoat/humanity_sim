#include "Utils.h"

#include "GameConfig.h"

double distance_to(double x1, double y1, double x2, double y2){
	double dx=x1-x2;
	double dy=y1-y2;
	double dist = std::sqrt(dx*dx+dy*dy);
	return dist;
	
}

void log_text(const std::string& english, const std::string& magyar) {
	switch (GameConfig::get_instance().get_sfml_lang()) {
		case Language::ENGLISH:
			std::cout <<"SFML | " << english << std::endl;
			break;
		case Language::MAGYAR:
			std::cout <<"SFML | " << magyar << std::endl;
			break;
		default:
			break;
	}
}

void warn_text(const std::string& english, const std::string& magyar,int config_minimum) {
	if(GameConfig::get_instance().get_config_level()>=config_minimum){
		switch (GameConfig::get_instance().get_lang()) {
			case Language::ENGLISH:
				std::cout << english << std::endl;
				break;
			case Language::MAGYAR:
				std::cout << magyar << std::endl;
				break;
			default:
				break;
		}
	}
}