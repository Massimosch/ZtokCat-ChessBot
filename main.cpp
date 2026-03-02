#include <iostream>
#include "kayttoliittyma.h"
#include "asema.h"
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include "peli.h"
#include <cstdlib>
#include <chrono>
using namespace std; 

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
	auto start = chrono::steady_clock::now();
	wcout << "Ultimate ZtokCät ChessBot! \nTervetuloa kokeilemaan onneanne...\n" << endl;
	int lopetus = 100;
	vector<Siirto> lista;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	
	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());

    system("cls");

	int koneenVari = peli.getKoneenVari();
	asema.setSiirtovuoro(0);

	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			auto move_start = chrono::steady_clock::now();
			MinMaxPaluu paluu;
			paluu = asema.minimax_multithread(-100000, 100000, 4);
			wcout << L"Evaluaatio Arvo: " << paluu._evaluointiArvo << endl;
			if (paluu._evaluointiArvo <= -100000 || paluu._evaluointiArvo >= 100000) lopetus = 0;
			siirto = paluu._parasSiirto;
			auto move_end = chrono::steady_clock::now();
			auto move_duration = chrono::duration_cast<chrono::milliseconds>(move_end - move_start);

			wcout << L"Time: " << move_duration.count() << L" ms" << endl;
		}
		else {
			auto move_start = chrono::steady_clock::now();
			MinMaxPaluu paluu;
			paluu = asema.minimax_multithread(-100000, 100000, 4);
			wcout << L"Evaluaatio Arvo: " << paluu._evaluointiArvo << endl;
			if (paluu._evaluointiArvo <= -100000 || paluu._evaluointiArvo >= 100000) lopetus = 0;
			siirto = paluu._parasSiirto;
			auto move_end = chrono::steady_clock::now();
			auto move_duration = chrono::duration_cast<chrono::milliseconds>(move_end - move_start);

			wcout << L"Time: " << move_duration.count() << L" ms" << endl;
			// Pelaajan siirto
			//wcout << "Siirtovuoro on pelaajalla" << endl;
			//
			//bool validInput = false;
			//while (!validInput) {
			//	siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(&asema);
			//	if (find(lista.begin(), lista.end(), siirto) != lista.end()+1) { // etsii onko siirto laillinen.
			//		validInput = true;
			//	}
			//	else {
			//		wcout << "Laita laillinen siirto!" << endl;
			//	}
			//}
			
		}
		asema.paivitaAsema(&siirto);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(end - start);

	wcout << L"Time in match: " << duration.count() << L" s" << endl;

	return 0;
}
