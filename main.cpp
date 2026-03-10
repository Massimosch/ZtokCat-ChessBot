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

#define PLAY_AGAINSTS_SELF
#define DEPTH 6

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
	auto start = chrono::steady_clock::now();
	wcout << "Ultimate ZtokCät ChessBot! \nTervetuloa kokeilemaan onneanne...\n" << endl;
	int lopetus = 100;
	vector<Siirto> lista;
	vector<Asema> asematLista;
	lista.reserve(218);
	asematLista.reserve(50);
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
			wcout << "Peli loppui" << endl;
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			auto move_start = chrono::steady_clock::now();
			MinMaxPaluu paluu;
			paluu = asema.minimax_multithread(-100000, 100000, DEPTH);
			wcout << L"Evaluaatio Arvo: " << paluu._evaluointiArvo << endl;
			siirto = paluu._parasSiirto;
			auto move_end = chrono::steady_clock::now();
			auto move_duration = chrono::duration_cast<chrono::milliseconds>(move_end - move_start);

			wcout << L"Time: " << move_duration.count() << L" ms" << endl;
		}
		else {

			auto move_start = chrono::steady_clock::now();
			#ifdef PLAY_AGAINSTS_SELF
				MinMaxPaluu paluu;
				paluu = asema.minimax_multithread(-100000, 100000, DEPTH);
				wcout << L"Evaluaatio Arvo: " << paluu._evaluointiArvo << endl;
				siirto = paluu._parasSiirto;
			#else
				wcout << "Siirtovuoro on pelaajalla" << endl;
				siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(&asema);
				while (siirto.getUndoValue() > 0) {
					if (asematLista.size() >= 2) {
						asema = asematLista[asematLista.size() - 2];
						asematLista.pop_back();
						asematLista.pop_back();
					}
					
					Kayttoliittyma::getInstance()->piirraLauta();
					siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(&asema);
					
				}
			#endif 
			auto move_end = chrono::steady_clock::now();
			auto move_duration = chrono::duration_cast<chrono::milliseconds>(move_end - move_start);
			wcout << L"Time: " << move_duration.count() << L" ms" << endl;
		}
		asematLista.push_back(asema);
		asema.paivitaAsema(&siirto);
		if (asema.ovatkoKuninkaatOlemassa() == false) {
			asema = asematLista[asematLista.size() - 2];
			asematLista.pop_back();
			asematLista.pop_back();
			Kayttoliittyma::getInstance()->piirraLauta();
			wcout << "Hyvin laiton siirto" << endl;
		}
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(end - start);

	wcout << L"Time in match: " << duration.count() << L" s" << endl;

	return 0;
}
