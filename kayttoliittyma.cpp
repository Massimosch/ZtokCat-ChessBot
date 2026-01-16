#include <iostream>
#include <string>
#include "kayttoliittyma.h"

#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
    #include <fcntl.h>
#endif

using namespace std;

Kayttoliittyma* Kayttoliittyma::instance = 0;

Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}

#ifdef _WIN32
void Kayttoliittyma::piirraLauta()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	bool drawDark = true;

	for (int x = 0; x <= 7; x++) {
		for (int y = 0; y <= 7; y++) {
			
			if (drawDark) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKTILE_INTENSITY | DARKTILE_RED |
					DARKTILE_GREEN | DARKTILE_BLUE);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTTILE_INTENSITY | LIGHTTILE_RED |
					LIGHTTILE_GREEN | LIGHTTILE_BLUE);
			}

			if (_asema->_lauta[x][y] == NULL) wcout << "   ";
			else {
				wcout << " ";
				wcout << _asema->_lauta[x][y]->getUnicode();
				wcout << " ";
			}

			drawDark = !drawDark;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes);
		}

		wcout << "\n";
		drawDark = !drawDark;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes);
	}
}
#endif


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
