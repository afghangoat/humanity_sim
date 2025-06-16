#include "button.h"

namespace ui{
	Button::Button(int px, int py, int width, int height, const std::string& spritepath): x(px), y(py), width(width), height(height), callback(nullptr) {
		clicked=false;
		hovered=false;
		states.blendMode = sf::BlendAdd;
		
		setTexture(spritepath);
		setPosition(px,py);
	}

	void Button::setCallback(std::function<void()> func) {
		callback = func;
	}

	void Button::try_hover_animation(int mX, int mY){
		if(mX >= x && mX <= x + width && mY >= y && mY <= y + height){
			hovered=true;
		} else {
			hovered=false;
		}
	}

	void Button::onClick(bool mc) {
		if (hovered==true&&mc==true) {
			if(clicked==false&&callback){
				clicked=true;
				callback();
			}
		} else {
			clicked=false;
		}
	}
	
	bool Button::setTexture(const std::string& filename) {
		
		sf::Texture* sharedTexture = TextureManager::getInstance().loadTexture(filename);
		
        if (!sharedTexture) {
            return false;
        }
		
        sprite.setTexture(*sharedTexture);
		
        return true;
	}
	void Button::setPosition(double x, double y) {
		if(x>0.0&&y>0.0){
			sprite.setPosition(x, y);
		}
	}
	void Button::draw(sf::RenderWindow& window) {
		if(hovered==true){
			sprite.setScale(1.0f, 1.0f);
			sprite.setColor(sf::Color(255, 255, 255, 128));
			window.draw(sprite,states);
			
			sprite.setScale(1.25f, 1.25f);
			sprite.setColor(sf::Color::White);
		} else {
			sprite.setScale(1.0f, 1.0f);
		}
		window.draw(sprite);
	}
}