#pragma once

///////////////////////////////////////
////Main header
///////////////////////////////////////

#include<iostream>
#include"TEXT.h"
#include"States_enum.h"
#include<SFML/Graphics.hpp>
#include<string>
#include<SFML/Window.hpp>
#include"BAT.h"
#include"Collision.h"
#include <ctime>



bool Game() {
	time_t t;
	srand(time(&t));
	sf::Vector2u defaultGameSize(1800, 1016);
	sf::RenderWindow window(sf::VideoMode(defaultGameSize.x, defaultGameSize.y), "TableTenis", sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(0, 0));

	sf::Texture mainTexture, gameTexture, ballTexture, batTexture_L, batTexture_R;
	if (!mainTexture.loadFromFile("Main_Texture.png")) { std::cout << TEXTS[0][Error_with_textures]; return EXIT_FAILURE; }
	if (!gameTexture.loadFromFile("Game_Texture.png")) { std::cout << TEXTS[0][Error_with_textures]; return EXIT_FAILURE; }
	if (!ballTexture.loadFromFile("BallTexture.png")) { std::cout << TEXTS[0][Error_with_textures]; return EXIT_FAILURE; }
	if (!batTexture_L.loadFromFile("left_bat.png")) { std::cout << TEXTS[0][Error_with_textures]; return EXIT_FAILURE; }
	if (!batTexture_R.loadFromFile("right_bat.png")) { std::cout << TEXTS[0][Error_with_textures]; return EXIT_FAILURE; }

	sf::Sprite sprite_menu, sprite_game;
	sprite_menu.setTexture(mainTexture);
	sprite_game.setTexture(gameTexture);

	sf::Font font;
	if (!font.loadFromFile("Anton-Regular.ttf")) { std::cout << TEXTS[0][Error_with_font]; }

	sf::Text text1, text2, text3, text4, text5, text6, text7;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text4.setFont(font);
	text5.setFont(font);
	text6.setFont(font);
	text7.setFont(font);

	float ballRadius = 9.124f;
	sf::CircleShape Ball(ballRadius, 100);
	Ball.setPosition(1700.f, 350.f);
	Ball.setTexture(&ballTexture);

	int game_state = main_menu, option{}, mouse_option{}, left_score{}, right_score{};
	float f_first_option_x = 96.f, f_first_option_y = 550.f;
	bool playing{};
	float X_multiplier = 1.0f, Y_multiplier = 1.0f;

	sf::Vector2i Mouse_Position{};
	sf::Vector2u gameSize{};

	BAT player1R_bat(batTexture_L, batTexture_R, true, defaultGameSize, true, X_multiplier, Y_multiplier, false);
	BAT bot_bat(batTexture_L, batTexture_R, false, defaultGameSize, true, X_multiplier, Y_multiplier, true);
	BAT player1L_bat(batTexture_L, batTexture_R, false, defaultGameSize, true, X_multiplier, Y_multiplier, false);
	BAT player2R_bat(batTexture_L, batTexture_R, true, defaultGameSize, false, X_multiplier, Y_multiplier, false);
	BAT player2L_bat(batTexture_L, batTexture_R, false, defaultGameSize, false, X_multiplier, Y_multiplier, false);

	float ballAngle = 0.0f;
	float batSpeed = 600.0f*X_multiplier;
	float ballSpeed = 600.0f*X_multiplier;
	float ballDirection{};
	int leftScore = 0, rightScore = 0;
	int game_event = game;
	int language = English;
	player1L_bat.resetPosition();
	player1R_bat.resetPosition();
	player2L_bat.resetPosition();
	player2R_bat.resetPosition();
	bot_bat.resetPosition();


	sf::Clock clock;

	while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Space)) std::cout << ballDirection << " | " << bot_bat.getPosition().x << " | " << bot_bat.getPosition().y << " | " << std::cos(ballAngle) << " | " << std::sin(ballAngle) << " | " << ballAngle << std::endl;

			if (evnt.Resized) {
				gameSize = window.getSize();
				X_multiplier = gameSize.x / (float)defaultGameSize.x;
				Y_multiplier = gameSize.y / (float)defaultGameSize.y;
				player1R_bat.resize(X_multiplier, Y_multiplier, gameSize);
				player1L_bat.resize(X_multiplier, Y_multiplier, gameSize);
				player2R_bat.resize(X_multiplier, Y_multiplier, gameSize);
				player2L_bat.resize(X_multiplier, Y_multiplier, gameSize);
				bot_bat.resize(X_multiplier, Y_multiplier, gameSize);
			}

			if ((game_event == pause || game_event == scores)) {
				player1L_bat.resetPosition();
				player1R_bat.resetPosition();
				player2L_bat.resetPosition();
				player2R_bat.resetPosition();
				bot_bat.resetPosition();
				ballSpeed = 600.0f*X_multiplier;
				Ball.setPosition(1650.f*X_multiplier, 350.f*Y_multiplier);
				ballDirection = 0.0f;
				ballAngle = 0.0f;

				if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Escape)) {
					game_state = main_menu;
					game_event = game;
					leftScore = 0;
					rightScore = 0;
				}
			}
			else if ((evnt.type == sf::Event::KeyPressed) && game_state != main_menu && (evnt.key.code == sf::Keyboard::Escape)) { game_event = pause; playing = false; }


			if (evnt.type == sf::Event::MouseMoved) {
				Mouse_Position = sf::Mouse::getPosition(window);
			}
			//if (evnt.mouseButton.button == sf::Mouse::Left) std::cout << "mouse:" << Mouse_Position.x << ":\t" << Mouse_Position.y << std::endl;

			if (game_state == main_menu) {

				if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::E)) { language = English; }
				if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::P)) { language = Polish; }
				if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::I)) { language = Italian; }
				if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::F)) { language = French; }

				if (option == 0) {
					//std::cout << "option" << option << std::endl;
					if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Down)) { option = 1; }
					else if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Up)) { option = 4; }

				}
				if (option == 1) {
					//std::cout << "option" << option << std::endl;
					if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Down)) { option = 2; }
					else if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Up)) { option = 4; }
					else if (((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Enter)) ||
							(mouse_option == 1 && evnt.mouseButton.button == sf::Mouse::Left)) { 
						game_state = single_player_game; 
						option = mouse_option = 0;
						playing = true;
					}
				}
				else if (option == 2) {
					//std::cout << "option" << option << std::endl;
					if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Down)) { option = 3; }
					else if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Up)) { option = 1; }
					else if (((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Enter)) ||
						(mouse_option == 2 && evnt.mouseButton.button == sf::Mouse::Left)) { 
						game_state = two_player_game;
						option = mouse_option = 0;
						playing = true;
					}
				}
				else if (option == 3) {
					//std::cout << "option" << option << std::endl;
					if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Down)) { option = 4; }
					else if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Up)) { option = 2; }
					else if (((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Enter)) ||
						(mouse_option == 3 && evnt.mouseButton.button == sf::Mouse::Left)) { 
						game_state = double_game;
						option = mouse_option = 0;
						playing = true;
					}
				}
				else if (option == 4) {
					//std::cout << "option" << option << std::endl;
					if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Down)) { option = 1; }
					else if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Up)) { option = 3; }
					else if (((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Enter)) ||
						(mouse_option == 4 && evnt.mouseButton.button == sf::Mouse::Left)) { window.close(); }
				}
			}

			//Set default start valuables to start
			if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Enter) ||
				(mouse_option == 4 && evnt.mouseButton.button == sf::Mouse::Left))
			{
				if (!playing)
				{
					playing = true;

					if (game_event == scores || game_state == main_menu) {
						leftScore = 0;
						rightScore = 0;
						clock.restart();
					}
					game_event = game;
					bot_bat.resetPosition();
					do
					{
						ballAngle = (std::rand() % 90 - 45) * 2 * 3.14f / 180;
					} while (std::abs(std::cos(ballAngle)) < 0.3f);
				}
			}
			
		}
		
		window.clear();

		if (game_state == main_menu) {

				window.draw(sprite_menu);
				text1.setCharacterSize(70);
				text2.setCharacterSize(70);
				text3.setCharacterSize(70);
				text4.setCharacterSize(70);
				text5.setCharacterSize(30);
				text1.setPosition(100.f*X_multiplier, 550.f*Y_multiplier);
				text2.setPosition(100.f*X_multiplier, 630.f*Y_multiplier);
				text3.setPosition(100.f*X_multiplier, 710.f*Y_multiplier);
				text4.setPosition(100.f*X_multiplier, 790.f*Y_multiplier);
				text5.setPosition(gameSize.x - 450.0f*X_multiplier, 780.0f*Y_multiplier);
				text1.setString(TEXTS[language][main_menu_single]);
				text2.setString(TEXTS[language][main_menu_two]);
				text3.setString(TEXTS[language][main_menu_double]);
				text4.setString(TEXTS[language][main_menu_out]);
				text5.setString(TEXTS[language][languages]);

				if (((f_first_option_x*X_multiplier) < Mouse_Position.x) &&
					(Mouse_Position.x < ((f_first_option_x + 647.f)*X_multiplier)) &&
					((f_first_option_y*Y_multiplier) < Mouse_Position.y) &&
					(Mouse_Position.y < ((f_first_option_y + 80.f)*Y_multiplier))) {
					mouse_option = 1;
				}
				else if (((f_first_option_x*X_multiplier) < Mouse_Position.x) &&
					(Mouse_Position.x < ((f_first_option_x + 610.f)*X_multiplier)) &&
					(((f_first_option_y + 81.f)*Y_multiplier) < Mouse_Position.y) &&
					(Mouse_Position.y < ((f_first_option_y + 163.f)*Y_multiplier))) {
					mouse_option = 2;
				}
				else if (((f_first_option_x*X_multiplier) < Mouse_Position.x) &&
					(Mouse_Position.x < ((f_first_option_x + 910.f)*X_multiplier)) &&
					(((f_first_option_y + 164.f)*Y_multiplier) < Mouse_Position.y) &&
					(Mouse_Position.y < ((f_first_option_y + 241.f)*Y_multiplier))) {
					mouse_option = 3;
				}
				else if (((f_first_option_x*X_multiplier) < Mouse_Position.x) &&
					(Mouse_Position.x < ((f_first_option_x + 231.f)*X_multiplier)) &&
					(((f_first_option_y + 242.f)*Y_multiplier) < Mouse_Position.y) &&
					(Mouse_Position.y < ((f_first_option_y + 323.f)*Y_multiplier))) {
					mouse_option = 4;
				}
				else { 
					mouse_option = 0;
				}

				if (mouse_option != 0) { option = mouse_option; }

				if (option == 1) {
					text1.setFillColor(sf::Color::Yellow);
					text2.setFillColor(sf::Color::Red);
					text3.setFillColor(sf::Color::Red);
					text4.setFillColor(sf::Color::Red);
				}
				else if (option == 2) {
					text2.setFillColor(sf::Color::Yellow);
					text1.setFillColor(sf::Color::Red);
					text3.setFillColor(sf::Color::Red);
					text4.setFillColor(sf::Color::Red);
				}
				else if (option == 3) {
					text3.setFillColor(sf::Color::Yellow);
					text1.setFillColor(sf::Color::Red);
					text2.setFillColor(sf::Color::Red);
					text4.setFillColor(sf::Color::Red);
				}
				else if (option == 4) {
					text4.setFillColor(sf::Color::Yellow);
					text1.setFillColor(sf::Color::Red);
					text2.setFillColor(sf::Color::Red);
					text3.setFillColor(sf::Color::Red);
				}
				else {
					text1.setFillColor(sf::Color::Red);
					text2.setFillColor(sf::Color::Red);
					text3.setFillColor(sf::Color::Red);
					text4.setFillColor(sf::Color::Red);
				}
				window.draw(text1);
				window.draw(text2);
				window.draw(text3);
				window.draw(text4);
				window.draw(text5);
			}
		else if (game_state != main_menu) {

			window.draw(sprite_game);

			const char* Scores[]{ "0", "1", "2", "3",
				"4", "5", "6", "7", "8", "9", "10",
				"11", "12", "13", "14", "15", "16",
				"17", "18", "19", "20", "21"};

			if (playing) {
				float deltaTime = clock.restart().asSeconds();
				const char* Up = "Up";
				const char* Down = "Down";
				const char* Right = "Right";
				const char* Left = "Left";

				// Check the collisions between ball and bats
				Collision Ball_confrontation(Ball);

				if (Ball_confrontation.Check(player1R_bat))
				{
					ballSpeed *= 1.05f;
					ballAngle = Ball_confrontation.moveAngle(player1R_bat, gameSize, deltaTime, ballDirection, ballSpeed);
				}

				switch (game_state) {

				case single_player_game:
					if (Ball_confrontation.Check(bot_bat))
					{
						ballSpeed *= 1.05f;
						ballAngle = Ball_confrontation.moveAngle(bot_bat, gameSize, deltaTime, ballDirection, ballSpeed);
					}
					break;

				case double_game:
					if (Ball_confrontation.Check(player2R_bat))
					{
						ballSpeed *= 1.05f;
						ballAngle = Ball_confrontation.moveAngle(player2R_bat, gameSize, deltaTime, ballDirection, ballSpeed);
					}

					if (Ball_confrontation.Check(player2L_bat))
					{
						ballSpeed *= 1.05f;
						ballAngle = Ball_confrontation.moveAngle(player2L_bat, gameSize, deltaTime, ballDirection, ballSpeed);
					}

				case two_player_game:
					if (Ball_confrontation.Check(player1L_bat))
					{
						ballSpeed *= 1.05f;
						ballAngle = Ball_confrontation.moveAngle(player1L_bat, gameSize, deltaTime, ballDirection, ballSpeed);
					}
					break;
				}

				// Check collisions between the ball and the screen and score
				int collision{};

				if (Ball.getPosition().x - ballRadius < 0.f)
				{
					collision = 2;
				}
				else if (Ball.getPosition().x + ballRadius > gameSize.x)
				{
					collision = 1;
				}
				else if (Ball.getPosition().y - ballRadius < 0.f ||
					Ball.getPosition().y + ballRadius > gameSize.y)
				{
					if (Ball.getPosition().x - ballRadius < gameSize.x / 2.0f) {
						collision = 2;
					}
					else if (Ball.getPosition().x - ballRadius > gameSize.x / 2.0f) {
						collision = 1;
					}
				}

				if (collision != 0) {

					ballDirection = 0;
					ballSpeed = 600.0f * X_multiplier;

					do
					{
						ballAngle = (std::rand() % 360) * 2 * (float)3.145 / 360;
					} while (std::abs(std::cos(ballAngle)) < 0.90f);

					if (rightScore < 21 && leftScore < 21) {
						if (collision == 1) {
							leftScore += 1;
							Ball.setPosition(150.f*X_multiplier, 666.f*Y_multiplier);
							if(leftScore == 21){
								game_event = scores;
								playing = false;
							}
						}
						else if (collision == 2) {
							rightScore += 1;
							Ball.setPosition(1650.f*X_multiplier, 350.f*Y_multiplier);
							if (rightScore == 21) {
								game_event = scores;
								playing = false;
							}
						}
					}
				}
				Ball.move(std::cos(ballAngle) * ballDirection, std::sin(ballAngle) * ballDirection);

				//First player of right side of table controls
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					player1R_bat.move(deltaTime, Up);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					player1R_bat.move(deltaTime, Down);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					player1R_bat.move(deltaTime, Left);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					player1R_bat.move(deltaTime, Right);
				}
				if (game_state == single_player_game)
				{
					bot_bat.move(deltaTime, Ball, ballAngle, ballDirection);
				}
				else if (game_state == two_player_game || game_state == double_game)
				{
					//First player of left side of table controls
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
						player1L_bat.move(deltaTime, Up);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						player1L_bat.move(deltaTime, Down);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						player1L_bat.move(deltaTime, Left);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						player1L_bat.move(deltaTime, Right);
					}

					if (game_state == double_game) {
						//Second player of right side of table controls
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
							player2R_bat.move(deltaTime, Up);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
							player2R_bat.move(deltaTime, Down);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
							player2R_bat.move(deltaTime, Left);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
							player2R_bat.move(deltaTime, Right);
						}

						//Second player of left side of table controls
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
							player2L_bat.move(deltaTime, Up);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
							player2L_bat.move(deltaTime, Down);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
							player2L_bat.move(deltaTime, Left);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
							player2L_bat.move(deltaTime, Right);
						}
					}
				}

				//Scores displaying on table
				text1.setFillColor(sf::Color::White);
				text2.setFillColor(sf::Color::White);
				text7.setFillColor(sf::Color::White);
				text1.setCharacterSize(200);
				text2.setCharacterSize(200);
				text7.setCharacterSize(200);
				text1.setPosition(665.0f* X_multiplier, 385.0f* Y_multiplier);
				text2.setPosition(1035.0f*X_multiplier, 385.0f*Y_multiplier);
				text1.setString(Scores[leftScore]);
				text2.setString(Scores[rightScore]);
			}
			else
			{
				if (game_event == scores) {

					text1.setFillColor(sf::Color::Red);
					text2.setFillColor(sf::Color::Yellow);
					text3.setFillColor(sf::Color::White);
					text5.setFillColor(sf::Color::White);
					text6.setFillColor(sf::Color::White);
					text4.setFillColor(sf::Color::Yellow);
					text7.setFillColor(sf::Color::Yellow);

					if (leftScore == 21) {
						text2.setString(TEXTS[language][left_side_win]);
					}
					if (rightScore == 21) {
						text2.setString(TEXTS[language][right_side_win]);
					}

					if (language == English) {
						text1.setPosition((gameSize.x - 508.6957f*X_multiplier) / 2.0f, 200.0f*Y_multiplier);
						text2.setPosition((gameSize.x - 408.0745f*X_multiplier) / 2.0f, 400.0f*Y_multiplier);
						text4.setPosition((gameSize.x - 497.5155f*X_multiplier) / 2.0f, 630.0f*Y_multiplier);
						text7.setPosition((gameSize.x - 290.6832f*X_multiplier) / 2.0f, 690.0f*Y_multiplier);
					}
					else if (language == Polish) {
						text1.setPosition((gameSize.x - 486.3354f*X_multiplier) / 2.0f, 200.0f*Y_multiplier);
						text2.setPosition((gameSize.x - 598.1366f*X_multiplier) / 2.0f, 400.0f*Y_multiplier);
						text4.setPosition((gameSize.x - 816.1491f*X_multiplier) / 2.0f, 630.0f*Y_multiplier);
						text7.setPosition((gameSize.x - 519.8758f*X_multiplier) / 2.0f, 690.0f*Y_multiplier);
					}
					else if (language == Italian) {
						text1.setPosition((gameSize.x - 586.9565f*X_multiplier) / 2.0f, 200.0f*Y_multiplier);
						text2.setPosition((gameSize.x - 603.7267f*X_multiplier) / 2.0f, 400.0f*Y_multiplier);
						text4.setPosition((gameSize.x - 894.4099f*X_multiplier) / 2.0f, 630.0f*Y_multiplier);
						text7.setPosition((gameSize.x - 654.0373f*X_multiplier) / 2.0f, 690.0f*Y_multiplier);
					}
					else if (language == French) {
						text1.setPosition((gameSize.x - 654.0373f*X_multiplier) / 2.0f, 200.0f*Y_multiplier);
						text2.setPosition((gameSize.x - 603.7267f*X_multiplier) / 2.0f, 400.0f*Y_multiplier);
						text4.setPosition((gameSize.x - 855.2795f*X_multiplier) / 2.0f, 630.0f*Y_multiplier);
						text7.setPosition((gameSize.x - 592.5466f*X_multiplier) / 2.0f, 690.0f*Y_multiplier);
					}


					text3.setPosition(790.0f*X_multiplier, 530.0f*Y_multiplier);
					text6.setPosition(957.0f*X_multiplier, 530.0f*Y_multiplier);
					text5.setPosition(891.0f*X_multiplier, 530.0f*Y_multiplier);
					text1.setCharacterSize(150);
					text1.setString(TEXTS[language][scores_title]);
					text2.setCharacterSize(70);
					text3.setCharacterSize(70);
					text3.setString(Scores[leftScore]);
					text5.setCharacterSize(70);
					text5.setString(":");
					text6.setCharacterSize(70);
					text6.setString(Scores[rightScore]);
					text4.setCharacterSize(50);
					text4.setString(TEXTS[language][win_instruction1]);
					text7.setCharacterSize(50);
					text7.setString(TEXTS[language][win_instruction2]);
					window.draw(text3);
					window.draw(text4);
					window.draw(text5);
					window.draw(text6);
					window.draw(text7);
				}
				else if (game_event == pause) {

					if (language == English) {
						text1.setPosition((gameSize.x - 391.3043f*X_multiplier) / 2.0f, 200.f*Y_multiplier);
						text2.setPosition((gameSize.x - 542.236f*X_multiplier) / 2.0f, 500.f*Y_multiplier);
						text7.setPosition((gameSize.x - 620.4969f*X_multiplier) / 2.0f, 580.f*Y_multiplier);
					}
					else if (language == Polish) {
						text1.setPosition((gameSize.x- 386.9441f*X_multiplier)/2.0f, 200.f*Y_multiplier);
						text2.setPosition((gameSize.x - 872.0497f*X_multiplier) / 2.0f, 500.f*Y_multiplier);
						text7.setPosition((gameSize.x - 542.236f*X_multiplier) / 2.0f, 580.f*Y_multiplier);
					}
					else if (language == Italian) {
						text1.setPosition((gameSize.x- 592.5466f*X_multiplier)/2.0f, 200.f*Y_multiplier);
						text2.setPosition((gameSize.x - 983.8509f*X_multiplier) / 2.0f, 500.f*Y_multiplier);
						text7.setPosition((gameSize.x - 905.5901f*X_multiplier) / 2.0f, 580.f*Y_multiplier);
					}
					else if (language == French) {
						text1.setPosition((gameSize.x - 391.3043f*X_multiplier) / 2.0f, 200.f*Y_multiplier);
						text2.setPosition((gameSize.x - 1000.621f*X_multiplier) / 2.0f, 500.f*Y_multiplier);
						text7.setPosition((gameSize.x - 810.559f*X_multiplier) / 2.0f, 580.f*Y_multiplier);
					}

					text1.setCharacterSize(150);
					text1.setString(TEXTS[language][pause_message]);
					text2.setCharacterSize(70);
					text2.setString(TEXTS[language][pause_instruction1]);
					text7.setCharacterSize(70);
					text7.setString(TEXTS[language][pause_instruction2]);
					window.draw(text7);
				}
			}
			window.draw(text1);
			window.draw(text2);
			window.draw(Ball);
			window.draw(player1R_bat);

			if ((game_state == single_player_game) || (game_event == scores)) {
				//std::cout << "you are in single" << std::endl;
				window.draw(bot_bat);
			}
			else if ((game_state == two_player_game) || (game_event == scores)) {
				//std::cout << "you are in two" << std::endl;
				window.draw(player1L_bat);
			}
			else if ((game_state == double_game) || (game_event == scores)) {
				//std::cout << "you are in double" << std::endl;
				window.draw(player1L_bat);
				window.draw(player2R_bat);
				window.draw(player2L_bat);
			}
		}
		window.display();
	}
	return EXIT_SUCCESS;
}
