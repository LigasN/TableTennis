#pragma once
#include<SFML/Graphics.hpp>
#include"BAT.h"
#include<iostream>

class Collision
{
private:
	sf::CircleShape &attacker;
	int sideAttack{};
	float attackerDirection{};
	float attackerSpeed{};

public:
	Collision(sf::CircleShape &attacker);
	~Collision();
	float moveAngle(BAT &defender, sf::Vector2u& gameSize, float deltaTime, float &ballDirection, const float &attackerSpeed);
	bool Check(BAT &defender);
	sf::Vector2f getPosition();
	float getHalfSize();
};

