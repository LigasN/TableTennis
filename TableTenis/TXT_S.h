#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>

using namespace std;


																//tytul rysowany z pliku txt
void Title() {
	system("cls");
	fstream file;
	file.open("Title.txt", ios::in);
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();
	cout << endl;
}
																//zapisywanie do txt przyklad zastosowania time
void saver(int i) {

	fstream plik;
	plik.open("Wyniki.txt", ios::out | ios::app);
	plik << date() << endl;
	plik << time() << endl;
	plik << endl;
	if (plik.good())
	{
		//plik <<cos co chcemy zapisac;							/////
		cout << "Zapisano" << endl;
		plik << endl;
		plik.close();
	}
	else cout << "Nie uzyskano dostepu do pliku" << endl;
}
																//jak w nazwie
void wypis_z_pliku_txt() {
	//Title();
	fstream plik;
	plik.open("Wyniki.txt", ios::in);
	if (plik.good() == true) {
		string line;
		while (getline(plik, line))
		{
			cout << line << endl;
		}
		plik.close();
		cout << endl;
	}
	else cout << "Dostep do pliku zostal zabroniony!" << endl;
}
