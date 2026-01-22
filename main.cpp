#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "asema.h"
#include <random>

#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
    #include <fcntl.h>
#else
    #include <unistd.h>
#endif

using namespace std; 

int main()
{
	#ifdef _WIN32
    	_setmode(_fileno(stdout), _O_U16TEXT);
	#else
    	setlocale(LC_ALL, "");
	#endif


	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";

	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;

	#ifdef _WIN32
    	system("cls");
	#else
    	system("clear");
	#endif

	int koneenVari = peli.getKoneenVari();
	asema.setSiirtovuoro(0);

	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		/*if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}*/
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
			siirto = lista.front();
		}
		else {
			// Pelaajan siirto
			wcout << "Siirtovuoro on pelaajalla" << endl;
			siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		}
		
		asema.paivitaAsema(&siirto);
	}

	
	return 0;
}
