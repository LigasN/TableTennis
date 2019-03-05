#pragma once


typedef enum {
	Error = 0,
	Error_with_textures = 1,
	Error_with_font = 2,
	main_menu_single = 3,
	main_menu_two = 4,
	main_menu_double = 5,
	main_menu_out = 6,
	scores_title = 7,
	pause_message = 8,
	pause_instruction1 = 9,
	pause_instruction2 = 10,
	right_side_win = 11,
	left_side_win = 12,
	win_instruction1 = 13,
	win_instruction2 = 14,
	languages = 15
} TEXT_ID;

typedef enum Languages {
	English = 0,
	Polish = 1,
	Italian = 2,
	French = 3
} LANGUAGE_ID;

static const wchar_t* TEXTS[4][16]{
	{
	L"Nie oczekiwany blad\n\n",																	//0
	L"Blad pobierania tekstur\n\n",																//1
	L"Blad pobierania czcionek\n\n",															//2
	L"Singleplayer\n",																			//3
	L"Game for two\n",																			//4
	L"Double game\n",																			//5
	L"Exit\n",																					//6
	L"Scores!!!",																				//7
	L"Pause!",																					//8
	L"To start press Enter",																	//9
	L"To leave press Escape",																	//10
	L"RIGHT SIDE WIN!",																			//11
	L"LEFT SIDE WIN!",																			//12
	L"Press Enter to restart or",																//13
	L"Escape to exit",																			//14
	L"To change language press:\nE- English\nP- Polish\nI- Italian\nF- French"					//15
	},
	{
	L"",L"",L"",																				
	L"Ty VS Komputer\n",																		//3
	L"Gra dla dwojga\n",																		//4
	L"Ping-pongowy \"Debel\"\n",																//5
	L"Wyjœcie\n",																				//6
	L"Wyniki!!!",																				//7
	L"Pauza!",																					//8
	L"Aby kontynuowaæ kliknij Enter",															//9
	L"¯eby wyjœæ Escape",																		//10
	L"Prawa strona wygra³a!",																	//11
	L"Lewa strona wygra³a!",																	//12
	L"Kliknij Enter, ¿eby zagraæ ponownie, lub",												//13
	L"Escape, ¿eby opuœciæ grê",																//14
	L"¯eby zmieniæ jêzyk kliknij:\nE- Angielski\nP- Polski\nI- W³oski\nF- Francuski"			//15
	},
	{
	L"",L"",L"",
	L"Giocatore singolo\n",																		//3
	L"Gioco per due\n",																			//4
	L"Doppio gioco\n",																			//5
	L"Uscita\n",																				//6
	L"Risultati!!!",																			//7
	L"Intervallo!",																				//8
	L"Per continuare premi il tasto Invio",														//9
	L"Per uscire premi il tasto Escape",														//10
	L"VINCE IL LATO DESTRO!",																	//11
	L"VINCE IL LATO SINISTRO!",																	//12
	L"Per ricominciare premi il testo Invio oppure",											//13
	L"Per uscire premi il testo Escape",														//14
	L"Per cambiare la lingua premi:\nE- Inglese\nP- Polacco\nI- Italiano\nF- Francese"			//15
	},
	{
	L"",L"",L"",
	L"Joueur individuel\n",																		//3
	L"Jeu pour deux\n",																			//4
	L"Double jeu\n",																			//5
	L"Sortie\n",																				//6
	L"Résultats!!!",																			//7
	L"Pause!",																					//8
	L"Pour continuer appuyez sur Entrée",														//9
	L"Pour finir appuyez sur Echap",															//10
	L"LE CÔTÉ DROIT GAGNE!",																	//11
	L"LE CÔTÉ GAUCHE GAGNE!",																	//12
	L"Pour recommencer appuyez sur Entrée ou",													//13
	L"Pour finir appuyez sur Echap",															//14
	L"Pour changer la langue appuyez sur:\nE- Anglais\nP- Polonais\nI- Italien\nF- Français"	//15
	}
};