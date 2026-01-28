#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

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

	for (int y = 7; y >= 0; y--) {
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
		wcout << " " << (y + 1) << endl;
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
	std::wstring komento{};
	wcout << "Anna Siirto : ";
	wcin >> komento;
	if (komento[0] != 'T' || komento[0] != 'R' || komento[0] != 'L' || komento[0] != 'D' || komento[0] != 'K' || komento[0] != 'S') {}

	if (komento == L"0-0") {
		Siirto siirto(true, false);
		return siirto;
	}

	if (komento == L"0-0-0") {
		Siirto siirto(true, false);
		return siirto;
	}

	int alkuRuutuRivi{};
	if (komento[1] == 'A') alkuRuutuRivi = 1;
	if (komento[1] == 'B') alkuRuutuRivi = 2;
	if (komento[1] == 'C') alkuRuutuRivi = 3;
	if (komento[1] == 'D') alkuRuutuRivi = 4;
	if (komento[1] == 'E') alkuRuutuRivi = 5;
	if (komento[1] == 'F') alkuRuutuRivi = 6;
	if (komento[1] == 'G') alkuRuutuRivi = 7;
	if (komento[1] == 'H') alkuRuutuRivi = 8;
	alkuRuutuRivi--;
	int loppuRuutuRivi{};
	if (komento[4] == 'A') loppuRuutuRivi = 1;
	if (komento[4] == 'B') loppuRuutuRivi = 2;
	if (komento[4] == 'C') loppuRuutuRivi = 3;
	if (komento[4] == 'D') loppuRuutuRivi = 4;
	if (komento[4] == 'E') loppuRuutuRivi = 5;
	if (komento[4] == 'F') loppuRuutuRivi = 6;
	if (komento[4] == 'G') loppuRuutuRivi = 7;
	if (komento[4] == 'H') loppuRuutuRivi = 8;
	loppuRuutuRivi--;
	wcout << "\nVUORO (0:V, 1:M) = " << _asema->getSiirtovuoro() << " : " 
		<< komento[1] << "-" << komento[2] << " " << komento[4] << "-" << komento[5] << endl;

#ifdef DEBUG_RIVI
	wcout << "Komento : " << komento << endl;
	wcout << "Alkurivi : " << alkuRuutuRivi << endl;
	wcout << "Loppuruuturivi : " << loppuRuutuRivi << endl;
	wcout << "Alkuruudun sarake : " << (int)komento[2] - '0' << endl;
	wcout << "Loppuruudun sarake : " << (int)komento[5] - '0' << endl;
#endif //

	
	Siirto siirto(
		Ruutu(alkuRuutuRivi, (int)komento[2] - '0' - 1),
		Ruutu(loppuRuutuRivi, (int)komento[5] - '0' - 1));

	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	int val;
	wcout << "Valitse Ihmispelaajan vari (musta = 1, valkoinen = 0) : ";
	wcin >> val;
	return val;
}
