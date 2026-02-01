#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include <Windows.h>
#include "nappula.h"

using namespace std;

Kayttoliittyma* Kayttoliittyma::instance = 0;
bool drawDark{ false };

Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}

void Kayttoliittyma::piirraLauta()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x <= 7; x++) {
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), drawDark ? DARKTILE_COLOR : LIGHTTILE_COLOR);
			
			if (_asema->_lauta[y][x] == NULL) 
				wcout << "   ";
			else {
				wcout << " ";
				wcout << _asema->_lauta[y][x]->getUnicode();
				wcout << " ";
			}

			drawDark = !drawDark;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes);
		wcout << " " << 8 - y << endl;
		drawDark = !drawDark;
	}

	wcout << " A  B  C  D  E  F  G  H  ";
}

/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	wstring komento{};
	wcout << "Anna Siirto : ";
	wcin >> komento;
	if (komento.size() == 6) komento.erase(0, 1);
	if (komento == L"0-0") {
		Siirto siirto(true, false);
		return siirto;
	}
	if (komento == L"0-0-0") {
		Siirto siirto(true, false);
		return siirto;
	}
	int alkuRuutuSarake = komento[0] - 'A';
	int loppuRuutuSarake = komento[3] - 'A';
	wcout << "\nVUORO (0:V, 1:M) = " << _asema->getSiirtovuoro() << " : " 
		<< komento[0] << "-" << komento[1] << " " << komento[3] << "-" << komento[4] << endl;
	
	Siirto siirto(Ruutu(komento[1] - '0' - 1, alkuRuutuSarake), Ruutu(komento[4] - '0' - 1, loppuRuutuSarake));

	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	int val;
	wcout << "Valitse Ihmispelaajan vari (musta = 1, valkoinen = 0) : ";
	wcin >> val;
	return val;
}
