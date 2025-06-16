#include "Profession.h"


bool Profession::setTexture(const std::string& filename) {
	sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
	sf::Texture* BgTexture = TextureManager::getInstance().loadTexture("src/textures/profession_items/profession_background_icon.png");
	
    if (!sharedTexture || !BgTexture) {
        return false;
    }
	
    profession_image.setTexture(*sharedTexture);
	background_image.setTexture(*BgTexture);
    return true;
}

void Profession::setPosition(double x, double y) {
	background_image.setPosition(x, y);
	profession_image.setPosition(x+4, y+4);
}

void Profession::draw(sf::RenderWindow& window) {
	window.draw(background_image);
	window.draw(profession_image);
}

void Profession::load_profession(const std::string& new_profession){
	profession_string=new_profession;
	std::string base_path="src/textures/profession_items/";
	std::string image_name=new_profession;
	
	base_path+=image_name;
	base_path+=".png";
	
	setTexture(base_path);
}
Profession::Profession(const std::string& intype){
	load_profession(intype);
}

std::string Profession::to_string(){
	return profession_string;
}