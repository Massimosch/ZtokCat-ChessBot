#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	bool drawDark = true;

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 7; y++) {
			if (drawDark) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKTILE_INTENSITY | DARKTILE_RED |
					DARKTILE_GREEN | DARKTILE_BLUE);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTTILE_RED |
					LIGHTTILE_GREEN | LIGHTTILE_BLUE);
			}
			
			wcout << "   ";
			drawDark != drawDark;
			
		}

		wcout << "\n";
	}

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 7; y++) {
			if (_asema->_lauta[x][y] == NULL) continue;

			wcout << _asema->_lauta[x][y]->getUnicode();
		}
	}
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
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
