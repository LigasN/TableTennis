#pragma once

class BAT : public sf::Drawable	
{
private:
	sf::Vector2f batSize;
	sf::RectangleShape bat;
	float batSpeed;
	sf::Vector2u gameSize;
	bool right_side,  first_player, bot;
	sf::Texture bat_tex_L;
	sf::Texture bat_tex_R;
	float angle;
	float X_multiplier = 1, Y_multiplier = 1;

public:
	BAT();
	BAT(sf::Texture &bat_tex_L, sf::Texture &bat_tex_R, bool right_side,const sf::Vector2u& gameSize, bool first_player, const float &X_multiplier, const float &Y_multiplier, bool bot);
	~BAT();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	sf::Vector2f * getSize();
	void setRotation(float angle);
	void resize(const float &X_multiplier, const float &Y_multiplier, sf::Vector2u &gameSize);
	void setDefaultSpeed(float batSpeed);
	void setPosition(float axis_x, float axis_y);
	sf::Vector2f getPosition();
	float getSpeed();
	sf::Vector2f getOrigin();
	void setAngle(float angle);
	void resetPosition();
	void move(float deltaTime, const char* direction);
	void move(float deltaTime, sf::CircleShape& aim, float &ballAngle, const float &ballDirection);
	bool getRightSide();
	bool getBot();
};

