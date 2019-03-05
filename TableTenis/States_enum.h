#pragma once


typedef enum game_states {
	main_menu = 0, 
	single_player_game = 1, 
	two_player_game = 2, 
	double_game = 3
} STATES_ID;

typedef enum game_events {
	game = 0,
	scores = 1,
	pause = 2
} EVENTS_ID;

