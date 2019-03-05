#include "Collision.h"



Collision::Collision(sf::CircleShape & attacker) :
	attacker(attacker)
{
	this->attacker = attacker;
	attackerSpeed = 400.f;
}

Collision::~Collision()
{
}

float Collision::moveAngle(BAT & defender, sf::Vector2u& gameSize, float deltaTime, float &ballDirection, const float &attackerSpeed)
{
	sf::Vector2f size = *defender.getSize();
	float ballAngle{};
	float pi = 3.145f;
	float los = (std::rand() % 12 )* pi / 180;

	//if (!defender.getBot()) {
		if (defender.getRightSide()) {
			if (this->getPosition().y > defender.getPosition().y)
				ballAngle = pi + los;
			else
				ballAngle = pi - los;

			attacker.setPosition(defender.getPosition().x - attacker.getRadius() - size.x / 2 - 10.0f, attacker.getPosition().y);
		}
		else {
			if (this->getPosition().y > defender.getPosition().y)
				ballAngle = -los;
			else
				ballAngle = los;

			attacker.setPosition(defender.getPosition().x + attacker.getRadius() + size.x / 2 + 10.0f, attacker.getPosition().y);
		}
	//}
	//else {
	//	if (!defender.getRightSide()) {
	//		if (defender.getPosition().y > 200.0f && defender.getPosition().y < gameSize.y - 200.0f) {
	//			if (this->getPosition().y > defender.getPosition().y)
	//				ballAngle = los;
	//			else
	//				ballAngle = - los;
	//		}
	//		else if (defender.getPosition().y > gameSize.y - 200.0f) {
	//			ballAngle = (std::rand() % 30 + 2.0f) * pi / 180;
	//		}
	//		else if (defender.getPosition().y < 200.0f) {
	//			ballAngle = (std::rand() % 30 - 32.0f) * pi / 180;
	//		}
	//		attacker.setPosition(defender.getPosition().x + attacker.getRadius() + size.x, attacker.getPosition().y);
	//	}
	//	else {
	//		//To write
	//	}
	//}

	ballDirection = attackerSpeed * deltaTime;
	return ballAngle;
}

bool Collision::Check(BAT & defender)
{
	sf::Vector2f size = *defender.getSize();
	float dx = defender.getPosition().x - attacker.getPosition().x;
	float dy = defender.getPosition().y - attacker.getPosition().y;
	float intersectX = abs(dx) - (size.x/2.0f + getHalfSize());
	float intersectY = abs(dy) - (size.y/2.0f + getHalfSize());

	if (intersectX < 0.f && intersectY < 0.0f) {
		return true;
	}
	return false;
}

sf::Vector2f Collision::getPosition()
{
	return attacker.getPosition();
}

float Collision::getHalfSize()
{
	return attacker.getRadius();
}
