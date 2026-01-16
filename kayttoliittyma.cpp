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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKTILE_COLOR);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTTILE_COLOR);
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

		wcout << " " << 8 - x ;
		wcout << "\n";
		drawDark = !drawDark;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes);
	}

	wcout << " A ";
	wcout << " B ";
	wcout << " C ";
	wcout << " D ";
	wcout << " E ";
	wcout << " F ";
	wcout << " G ";
	wcout << " H ";
}
#endif


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	
	std::string komento;
	wcout << "Anna Siirto : ";
	cin >> komento;
	if (komento[0] != 'T' || komento[0] != 'R' || komento[0] != 'L' || komento[0] != 'D' || komento[0] != 'K' || komento[0] != 'S') {}
	int alkuRuutuRivi;
	if (komento[1] == 'A') alkuRuutuRivi = 1;
	if (komento[1] == 'B') alkuRuutuRivi = 2;
	if (komento[1] == 'C') alkuRuutuRivi = 3;
	if (komento[1] == 'D') alkuRuutuRivi = 4;
	if (komento[1] == 'E') alkuRuutuRivi = 5;
	if (komento[1] == 'F') alkuRuutuRivi = 6;
	if (komento[1] == 'G') alkuRuutuRivi = 7;
	if (komento[1] == 'H') alkuRuutuRivi = 8;
	int loppuRuutuRivi;
	if (komento[4] == 'A') loppuRuutuRivi = 1;
	if (komento[4] == 'B') loppuRuutuRivi = 2;
	if (komento[4] == 'C') loppuRuutuRivi = 3;
	if (komento[4] == 'D') loppuRuutuRivi = 4;
	if (komento[4] == 'E') loppuRuutuRivi = 5;
	if (komento[4] == 'F') loppuRuutuRivi = 6;
	if (komento[4] == 'G') loppuRuutuRivi = 7;
	if (komento[4] == 'H') loppuRuutuRivi = 8;
	Siirto siirto(Ruutu(alkuRuutuRivi, (int)komento[2] - '0'), Ruutu(loppuRuutuRivi, (int)komento[5] - '0'));


	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	int val;
	wcout << "Vastustajan vari (musta = 1, valkoinen = 0) : ";
	wcin >> val;
	return val;
}
