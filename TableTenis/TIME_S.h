
//funkcje do korzystania z czasu
#pragma once

#include<iostream>
#include<string>
#include<windows.h>

using namespace std;

#ifndef TIME
#define TIME   SYSTEMTIME st; GetLocalTime(&st);
#endif


string date() {
	TIME;
	string date;
	string dzien = to_string(st.wDay);
	string d = to_string(st.wDay);
	if (st.wDay < 10) {
		dzien = "0" + d;
	}
	string miesiac = to_string(st.wMonth);
	string mie = to_string(st.wMonth);
	if (st.wMonth < 10) {
		miesiac = "0" + mie;
	}
	string rok = to_string(st.wYear);
	string r = to_string(st.wYear);
	if (st.wYear < 10) {
		rok = "0" + r;
	}
	date = dzien + "." + miesiac + "." + rok;
	return date;
}

string time() {
	TIME;
	string time;
	string godzina = to_string(st.wHour);
	string g = to_string(st.wHour);
	if (st.wHour < 10) {
		godzina = "0" + g;
	}
	string minuta = to_string(st.wMinute);
	string min = to_string(st.wMinute);
	if (st.wMinute < 10) {

		minuta = "0" + min;
	}
	string sekunda = to_string(st.wSecond);
	string s = to_string(st.wSecond);
	if (st.wSecond < 10) {
		sekunda = "0" + s;
	}
	time = godzina + ":" + minuta + ":" + sekunda;
	return time;
}
