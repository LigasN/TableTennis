#include<SFML/Graphics.hpp>
#include"BAT.h"
#include<SFML/Window.hpp>
#include<math.h>
#include <ctime>
#include<iostream>

BAT::BAT()
{
	right_side = true;
	X_multiplier = 1;
	Y_multiplier = 1;
	gameSize = sf::Vector2u(1800, 1016);
	angle = 0;
	first_player = true;
	batSize = sf::Vector2f(26.f, 129.f);
	bat = sf::RectangleShape(batSize);
	bot = false;
	batSpeed = 600.f;
	if (bot) { batSpeed = 1000.0f; }
}

BAT::BAT(sf::Texture &bat_tex_L, sf::Texture &bat_tex_R, bool right_side, const sf::Vector2u & gameSize, bool first_player,const float &X_multiplier,const float &Y_multiplier, bool bot){
	this->bat_tex_L = bat_tex_L;
	this->bat_tex_R = bat_tex_R;
	this->gameSize = gameSize;
	this->right_side = right_side;
	this->first_player = first_player;
	this->X_multiplier = X_multiplier;
	this->Y_multiplier = Y_multiplier;
	this->bot = bot;
	batSize = sf::Vector2f(26.f*X_multiplier, 129.f*Y_multiplier);
	bat = sf::RectangleShape(batSize);
	bat.setTexture(&bat_tex_R);


	if (!right_side) {
		bat.setOrigin(batSize.x / 2.0f, batSize.y * 0.5f);
		angle = 180.f;
		bat.setRotation(angle);
		if (first_player) { setPosition(150.0f * X_multiplier, gameSize.y / 2.0f); }
		else { setPosition(50.f * X_multiplier, (gameSize.y * 1.2f) / 2.0f); }
	}
	else {
		bat.setOrigin(batSize.x / 2.0f, batSize.y * 0.5f);
		angle = 0.f;
		bat.setRotation(angle);
		if (first_player) { setPosition(gameSize.x - 150.f * X_multiplier, gameSize.y / 2.0f); }
		else { setPosition(gameSize.x - 50.f * X_multiplier, (gameSize.y * 1.2) / 2.0f); }
	}

	batSpeed = 600.f * X_multiplier;
	if (bot) { batSpeed = 1000.0f * X_multiplier; }
	bat.setTexture(&bat_tex_R);
}

BAT::~BAT()
{
}

void BAT::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->bat, state);
}

sf::Vector2f * BAT::getSize()
{
	return &batSize;
}

void BAT::setRotation(float angle)
{
	bat.setRotation(angle);
}

void BAT::resize(const float& X_multiplier, const float& Y_multiplier, sf::Vector2u &gameSize)
{
	this->gameSize = gameSize;
	batSize.x = batSize.x*X_multiplier;
	batSize.y = batSize.y*Y_multiplier;
}

void BAT::setDefaultSpeed(float batSpeed)
{
	this->batSpeed = batSpeed * X_multiplier;
}

void BAT::setPosition(float axis_x, float axis_y)
{
	bat.setPosition(axis_x * X_multiplier, axis_y * Y_multiplier);
}

sf::Vector2f BAT::getPosition()
{
	return bat.getPosition();
}

float BAT::getSpeed()
{
	return batSpeed;
}

sf::Vector2f BAT::getOrigin()
{
	return bat.getOrigin();
}

void BAT::setAngle(float angle)
{
	this->angle = angle;
	bat.setRotation(angle);
}

void BAT::resetPosition()
{
	if (!right_side) {
		angle = 180.f;
		bat.setRotation(angle);
		if (first_player) { setPosition(150.0f * X_multiplier, gameSize.y/2.0f); }
		else { setPosition(50.f * X_multiplier, (gameSize.y * 1.2f)/ 2.0f); }
	}
	else {
		angle = 0.f;
		bat.setRotation(angle);
		if (first_player) { setPosition(gameSize.x - 150.f * X_multiplier, gameSize.y / 2.0f); }
		else { setPosition(gameSize.x - 50.f * X_multiplier, (gameSize.y * 1.2) / 2.0f); }

	}
	//std::cout << "resetPosition\t" << this->getPosition().x << "\t" << this->getPosition().y << std::endl;
	batSpeed = 600.f * X_multiplier;
	if (bot) { batSpeed = 1000.0f * X_multiplier; }
	bat.setTexture(&bat_tex_R);
}

void BAT::move(float deltaTime, const char* direction)
{
	if (direction == "Up") {
		if (right_side) {
			bat.setTexture(&bat_tex_R);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.3f);
		}
		else {
			bat.setTexture(&bat_tex_L);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.3f);
			angle = 180.0f;
		}
	}
	else if (direction == "Down") {
		if (right_side) {
			bat.setTexture(&bat_tex_L);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.5f);
		}
		else {
			bat.setTexture(&bat_tex_R);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.5f);
			angle = 180.0f;
		}
	}
	bat.setRotation(angle);

	if (!bot) {
		if ((direction == "Up") && (this->getPosition().y - batSize.y / 2 > 0.f)) {
			bat.move(0.f, -batSpeed * deltaTime);
		}
		else if ((direction == "Down") && (this->getPosition().y + batSize.y / 2 < gameSize.y)) {
			bat.move(0.f, batSpeed*deltaTime);
		}
		if ((direction == "Left") &&
			((right_side) && (this->getPosition().x - batSize.x / 2 > 910.f*X_multiplier) ||
			((!right_side) && (this->getPosition().x - batSize.x / 2 > 0.f)))) {
			bat.move(-batSpeed * deltaTime, 0.f);
		}
		else if ((direction == "Right") &&
			((right_side) && (this->getPosition().x + batSize.x / 2 < gameSize.x) ||
			((!right_side) && (this->getPosition().x + batSize.x / 2 < 890.f*X_multiplier)))) {
			bat.move(batSpeed * deltaTime, 0.f);
		}
	}
}

void BAT::move(float deltaTime, sf::CircleShape& aim, float &ballAngle, const float &ballDirection){


	if (this->getPosition().y > aim.getPosition().y) {
		if (right_side) { 
			bat.setTexture(&bat_tex_R); 
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.3f);
		}
		else {
			bat.setTexture(&bat_tex_L);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.3f);
		}
	}
	else if (this->getPosition().y < aim.getPosition().y) {
		if (right_side) { 
			bat.setTexture(&bat_tex_L);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.5f);
		}
		else {
			bat.setTexture(&bat_tex_R);
			bat.setOrigin(batSize.x*0.5f, batSize.y*0.5f);
		}
	}

	bat.setRotation(angle);

	if (bot) {

		bool Up{};
		bool Right{};
		bool Down{};
		bool Left{};
		ballAngle = abs(ballAngle);
		sf::Vector2i botPosition(this->getPosition());
		sf::Vector2i crossPoint{};
		sf::Vector2i botDefaultPosition(100.0f * X_multiplier, gameSize.y/2.0f);
		sf::Vector2i ballPosition(aim.getPosition());
		sf::Vector2i aimSetPosition(1650.f * X_multiplier, 350.f * Y_multiplier);

		double ratioXY = std::sin(ballAngle) / std::cos(ballAngle);
		double ratioYX = std::cos(ballAngle) / std::sin(ballAngle);
		crossPoint.y = ballPosition.y - ratioXY * ballPosition.x;
		crossPoint.x = ballPosition.x - abs(ratioYX * ballPosition.y) + 200.0f * X_multiplier;
		if (crossPoint.y > 600.0f * Y_multiplier) crossPoint.y - batSize.y / 2.0f + 10.0f;
		if (crossPoint.y > 1000.0f * Y_multiplier) crossPoint.x = abs(ratioYX) * (crossPoint.y + bat.getSize().y + 50.0f - ballPosition.y) + 330.f * X_multiplier;
		if (ballAngle == 0 || (ballDirection == 0 && ballPosition.x > gameSize.x / 2.0f)) { crossPoint.x = crossPoint.y = 0.0f; bat.setPosition(botDefaultPosition.x, botDefaultPosition.y); }

		if (std::cos(ballAngle) < 0.0f && ballDirection != 0) {
			if (botPosition.y < gameSize.y - 90.0f * Y_multiplier && crossPoint.y > botPosition.y) { Down = true;  Up = false; }
			else if (botPosition.y > 50.0f && crossPoint.y < botPosition.y) { Down = false; Up = true; }
			else { Down = false; Up = false; }
			if ((crossPoint.x > botPosition.x || botPosition.x < 200.0f * X_multiplier) && botPosition.x < gameSize.x/2.0f) { Left = false; Right = true; }
			else if (crossPoint.x < botPosition.x && botPosition.x >= 200.0f * X_multiplier) { Left = true; Right = false; }
			else { Right = false; Left = false; }
		}
		else if (ballPosition.x < gameSize.x / 2.0f && ballDirection == 0) {
			if (botPosition.y < gameSize.y - bat.getSize().y / 2.0f && ballPosition.y > botPosition.y) { Down = true;  Up = false; }
			else if (botPosition.y > bat.getSize().y / 2.0f && ballPosition.y < botPosition.y) { Down = false; Up = true; }
			else { Down = false; Up = false; }
			if (ballPosition.x > botPosition.x) { Left = false; Right = true; }
			else if (ballPosition.x < botPosition.x) { Left = true; Right = false; }
			else { Right = false; Left = false; }
		}
		else if ((std::cos(ballAngle) > 0.0 && ballDirection != 0.0f) || (ballPosition.x > gameSize.x/2.0f && ballDirection == 0)){
			if (botPosition.y < gameSize.y - 50.0f * Y_multiplier && botDefaultPosition.y > botPosition.y) { Down = true;  Up = false; }
			else if (botPosition.y > 50.0f * Y_multiplier && botDefaultPosition.y < botPosition.y) { Down = false; Up = true; }
			else { Down = false; Up = false; }
			if (botDefaultPosition.x > botPosition.x) { Left = false; Right = true; }
			else if (botDefaultPosition.x < botPosition.x) { Left = true; Right = false; }
			else { Right = false; Left = false; }
		}


		if (Up) {
			bat.move(0.0f, -batSpeed*deltaTime);
		}
		if (Down) {
			bat.move(0.0f, batSpeed*deltaTime);
		}
		if (Left){
			bat.move(-batSpeed * deltaTime, 0.f);
		}
		if (Right) {
			bat.move(batSpeed * deltaTime, 0.f);
		}
	}
}

bool BAT::getRightSide()
{
	return right_side;
}

bool BAT::getBot()
{
	return bot;
}



