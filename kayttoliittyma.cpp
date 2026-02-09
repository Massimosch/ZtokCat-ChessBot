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

	wcout << " A  B  C  D  E  F  G  H  " << endl;
}

void Kayttoliittyma::piirraLauta(Asema* _asema) {
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

	wcout << " A  B  C  D  E  F  G  H  " << endl;
}

/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto(Asema* asema)
{
	wstring komento{};
	while (komento.size() < 5 || komento.size() > 6) {
		wcout << "Anna Siirto : ";
		wcin >> komento;
	}
	if (komento.size() == 6) komento.erase(0, 1);
	if (komento == L"0-0") {
		Siirto siirto(true, false);
		return siirto;
	}
	if (komento == L"0-0-0") {
		Siirto siirto(true, false);
		return siirto;
	}
	int alkuRuutuSarake = std::toupper(komento[0]) - 'A' - 1;
	int loppuRuutuSarake = std::toupper(komento[3]) - 'A' - 1;

	wcout << "\nVUORO (0:V, 1:M) = " << _asema->getSiirtovuoro() << " : " 
		<< komento[0] << "-" << komento[1] << " " << komento[3] << "-" << komento[4] << endl;
	
	Ruutu alkuruutu = Ruutu(alkuRuutuSarake + 1, 7 - (komento[1] - '0' - 1));
	Ruutu loppuruutu = Ruutu(loppuRuutuSarake + 1, 7 - (komento[4] - '0' - 1));
	Siirto siirto(alkuruutu, loppuruutu);
	siirto.getLoppuruutu().getRivi();
	siirto.getLoppuruutu().getRivi();
	if ((siirto.getLoppuruutu().getRivi() == 7 || siirto.getLoppuruutu().getRivi() == 0) 
		&& (asema->_lauta[siirto.getAlkuruutu().getRivi()][siirto.getAlkuruutu().getSarake()] == Asema::ms 
			|| asema->_lauta[siirto.getAlkuruutu().getRivi()][siirto.getAlkuruutu().getSarake()] == Asema::vs)) {
		
		string komento{};
		
		Nappula* miksikorotetaan{};
		bool inputvalid = false;
		

		while (!inputvalid) {
			wcout << "Miksi nappulaksi haluat korottaa? (väri + nappulan tyyppi. esim, m + t = mt)" << endl;
			cin >> komento;
			if (komento == "mt") miksikorotetaan = Asema::mt;
			if (komento == "mr") miksikorotetaan = Asema::mr;
			if (komento == "ml") miksikorotetaan = Asema::ml;
			if (komento == "md") miksikorotetaan = Asema::md;

			if (komento == "vt") miksikorotetaan = Asema::vt;
			if (komento == "vr") miksikorotetaan = Asema::vr;
			if (komento == "vl") miksikorotetaan = Asema::vl;
			if (komento == "vd") miksikorotetaan = Asema::vd;

			if (miksikorotetaan != nullptr) inputvalid = true;
			if (!inputvalid) wcout << "Laita korotettu nappula oikein kirjoitettuna esim, m + t = mt" << endl;
		}

		siirto = Siirto(alkuruutu, loppuruutu, miksikorotetaan);
	}

	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	int val;
	wcout << "Valitse Ihmispelaajan vari (musta = 1, valkoinen = 0) : ";
	wcin >> val;
	return val;
}
