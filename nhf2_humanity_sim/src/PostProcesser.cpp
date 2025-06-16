#include "PostProcesser.h"

PostProcesser::PostProcesser(){
	toggle_vignette(false);
	toggle_noise(false);
	toggle_chromatic_aberration(false);
	
	setTextureFor(vignette_sprite,"src/textures/vignette2.png");
	setTextureFor(noise_sprite,"src/textures/noise1_transparent_textures.png");
	setTextureFor(chromatic_aberration_sprite,"src/textures/chromatic_aberration_by_GDJ.png");
	overlay_enabled=false;
}

void PostProcesser::toggle_vignette(bool newval){
	vignette_enabled=newval;
}

void PostProcesser::toggle_noise(bool newval){
	noise_enabled=newval;
}
void PostProcesser::toggle_chromatic_aberration(bool newval){
	chromatic_aberration_enabled=newval;
}

bool PostProcesser::setTextureFor(sf::Sprite& what,const std::string& filename) {
	sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
	
    if (!sharedTexture) {
        return false;
    }
	
    what.setTexture(*sharedTexture);
    return true;
}

void PostProcesser::setRenderSize(double x, double y) {
	if(x<=0.0||y<=0.0){
		throw std::runtime_error("Nem lehet a render méret <=0.");
	}
	vignette_sprite.setScale(x / vignette_sprite.getLocalBounds().width, y / vignette_sprite.getLocalBounds().height);
	noise_sprite.setScale(x / noise_sprite.getLocalBounds().width, y / noise_sprite.getLocalBounds().height);
	chromatic_aberration_sprite.setScale(x / chromatic_aberration_sprite.getLocalBounds().width, y / chromatic_aberration_sprite.getLocalBounds().height);
	colorRect.setSize(sf::Vector2f(x,y));
}

void PostProcesser::setColorOverlay(int r, int g, int b, int a){
	if(a!=0){
		overlay_enabled=true;
	} else {
		overlay_enabled=false;
	}
	colorRect.setFillColor(sf::Color(r,g,b,a));
}

void PostProcesser::draw(sf::RenderWindow& window) {
	if(noise_enabled==true){
		window.draw(noise_sprite);
	}
	if(vignette_enabled==true){
		window.draw(vignette_sprite);
	}
	if(overlay_enabled==true){
		window.draw(colorRect);
	}
	if(chromatic_aberration_enabled==true){
		window.draw(chromatic_aberration_sprite);
	}
}