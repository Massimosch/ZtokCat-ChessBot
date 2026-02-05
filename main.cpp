#include <iostream>
#include "kayttoliittyma.h"
#include "asema.h"
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include "peli.h"
#include <cstdlib>
using namespace std; 

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

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
		/*if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(3);
			}
			else {
				paluu = asema.mini(3);
			}
			siirto = paluu._parasSiirto;
		}*/
		/*else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
			
		}*/
		if (asema.getSiirtovuoro() == koneenVari) {
			// Koneen siirto
			wcout << "Siirtovuoro on botilla" << endl;
			if (!lista.empty()) siirto = lista[rand() % lista.size()];
		    
		}
		else {
			// Pelaajan siirto
			wcout << "Siirtovuoro on pelaajalla" << endl;
			bool validSiirto = false;
			while (!validSiirto) {
				siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(&asema);
				validSiirto = true;
				if (siirto.onkoLyhytLinna() && asema.getOnkoMustaKTliikkunut()
					|| asema.getOnkoMustaKuningasLiikkunut() && asema.getSiirtovuoro() == 1) validSiirto = false;

				if (siirto.onkoPitkalinna() && asema.getOnkoMustaDTliikkunut()
					|| asema.getOnkoMustaKuningasLiikkunut() && asema.getSiirtovuoro() == 1) validSiirto = false;

			}
			
		}
		
		asema.paivitaAsema(&siirto);
	}

	
	return 0;
}
