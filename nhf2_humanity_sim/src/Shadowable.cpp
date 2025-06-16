#include "Shadowable.h"

bool Shadowable::setShadowTexture(const std::string& filename) {
    #ifndef MEMTRACE_FIX
		sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
			
		if (!sharedTexture) {
			return false;
		}
		shadow.setTexture(*sharedTexture);
	#else
		sf::Texture sharedTexture = TextureManager::getInstance().getTexture(filename);
		shadow.setTexture(sharedTexture);
	#endif
    shadow.setColor(sf::Color(0, 0, 0, shadow_strength));
    return true;
}

void Shadowable::setShadow(float ySize, float xSkew) {
	//Mirror
	shadow.setScale(1.0f, -ySize);

	shadow.setPosition(originalShadowPos.x-xSkew, originalShadowPos.y + height_offset*ySize);

	sf::Transform transform;
	transform.translate(shadow.getPosition());

	inner_skew=xSkew;
}

void Shadowable::setShadowDayNightCycle(float delta_time){
	float time_scaled=std::fmod(delta_time,GameConfig::get_instance().day_length);
	time_scaled=time_scaled/GameConfig::get_instance().day_length;
	time_scaled*=2*3.1415926;
	
	float time_corrected=std::sin(time_scaled);
	if(time_corrected>0){
		time_scaled/=3.1415926;
		setShadow(1.1f-time_corrected,time_scaled-0.5f);
	} else {
		setShadow(0.0f,0.0f);
	}
	
}

void Shadowable::setShadowPosition(double x, double y){
	originalShadowPos.x=x;
	originalShadowPos.y=y+height_offset;
	shadow.setPosition(originalShadowPos.x,originalShadowPos.y);
}

void Shadowable::drawShadow(sf::RenderWindow& window){
	sf::Transform shearTransform;
	shearTransform = sf::Transform(
		1, inner_skew * skew_offset, 0,
		0, 1, 0,
		0, 0, 1
	);
	
	sf::FloatRect bounds = shadow.getGlobalBounds();
	float yPos = shadow.getPosition().y;
	
	float shadowOffsetX = -inner_skew * skew_offset * (yPos + bounds.height);
	shearTransform.translate(shadowOffsetX, 0);

	sf::RenderStates states;
	states.transform = shearTransform;

	window.draw(shadow,states);
}
double Shadowable::get_height_offset() const{
	return height_offset;
}
int Shadowable::get_shadow_strength() const{
	return shadow_strength;
}
float Shadowable::get_skew_offset() const{
	return skew_offset;
}
void Shadowable::set_height_offset(double new_val){
	height_offset=new_val;
}
void Shadowable::set_shadow_strength(int new_val){
	shadow_strength=new_val;
}
void Shadowable::set_skew_offset(float new_val){
	skew_offset=new_val;
}