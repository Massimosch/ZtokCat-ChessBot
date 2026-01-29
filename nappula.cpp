#include <list>
#include <vector>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <iostream>
using namespace std;

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}

void Torni::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	if (asema->getSiirtovuoro() != this->getVari()) return;

	// Oikealle
	for (int x = sarake+1; x <= 7; x++) {
		if (asema->_lauta[rivi][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[rivi][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[rivi][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
		lista.push_back(newSiirto);
	}

	// Vasemmalle
	for (int x = sarake-1; x >= 0; x--) {
		if (asema->_lauta[rivi][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[rivi][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[rivi][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, rivi));
		lista.push_back(newSiirto);
	}

	// Ylös
	for (int y = rivi-1; y >= 0; y--) {
		if (asema->_lauta[y][sarake] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][sarake]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][sarake]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
		lista.push_back(newSiirto);
	}

	// Alas
	for (int y = rivi+1; y <= 7; y++) {
		if (asema->_lauta[y][sarake] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][sarake]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][sarake]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, y));
		lista.push_back(newSiirto);
	}
}

void Ratsu::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

	if (asema->getSiirtovuoro() != this->getVari()) return;
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (rivi - 1 >= 0 && sarake + 2 <= 7) {
		if (asema->_lauta[rivi - 1][sarake + 2] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake + 2]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 2, rivi - 1)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 2, rivi - 1)));
		}
	}

	if (rivi + 1 <= 7 && sarake + 2 <= 7) {
		if (asema->_lauta[rivi + 1][sarake + 2] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake + 2]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 2, rivi + 1)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 2, rivi + 1)));
		}
	}
		
	if (rivi - 2 >= 0 && sarake + 1 <= 7) {
		if (asema->_lauta[rivi - 2][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi - 2][sarake + 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi - 2)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi - 2)));
		}
	}
		
	if (rivi + 2 <= 7 && sarake + 1 <= 7) {
		if (asema->_lauta[rivi + 2][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi + 2)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi + 2)));
		}
	}

	if (rivi - 1 >= 0 && sarake - 2 >= 0) {
		if (asema->_lauta[rivi - 1][sarake - 2] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake - 2]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 2, rivi - 1)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 2, rivi - 1)));
		}
	}

	if (rivi + 1 <= 7 && sarake - 2 >= 0) {
		if (asema->_lauta[rivi + 1][sarake - 2] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake - 2]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 2, rivi + 1)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 2, rivi + 1)));
		}
	}

	if (rivi + 2 <= 7 && sarake - 1 >= 0) {
		if (asema->_lauta[rivi + 2][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi + 2][sarake - 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi + 2)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi + 2)));
		}
	}

	if (rivi - 2 >= 0 && sarake - 1 >= 0) {
		if (asema->_lauta[rivi - 2][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi - 2][sarake - 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi - 2)));
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi - 2)));
		}
	}
}

void Lahetti::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (asema->getSiirtovuoro() != this->getVari()) return;

		//Oikealle ylös
	for (int y = rivi - 1, x = sarake + 1; x <= 7 && y >= 0; x++, y--) {
		if (asema->_lauta[y][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
		lista.push_back(newSiirto);
	}

	//Oikealle alas
	for (int y = rivi + 1, x = sarake + 1; x <= 7 && y <= 7; x++, y++) {
		if (asema->_lauta[y][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
		lista.push_back(newSiirto);
	}

	//Vasemmalle ylös - TARKISTA KULMISTA TOIMIIKO ESIM 0, 0
	for (int x = sarake - 1, y = rivi - 1; x >= 0 && y >= 0; x--, y--) {
		if (asema->_lauta[y][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
		lista.push_back(newSiirto);
	}

	//Vasemmalle alas
	for (int x = sarake + 1, y = rivi + 1; x >= 0 && y <= 7; x--, y++) {
		if (asema->_lauta[y][x] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[y][x]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[y][x]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, y));
		lista.push_back(newSiirto);
	}
}

void Daami::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}

void Kuningas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.
	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/
	if (asema->getSiirtovuoro() != this->getVari()) return;
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (rivi + 1 <= 7) {
		if (asema->_lauta[rivi + 1][sarake] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi + 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi+1)));
		}
	}
	
	if (rivi - 1 >= 0) {
		if (asema->_lauta[rivi - 1][sarake] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 1)));
		}
	}

	if (sarake + 1 <= 7) {
		if (asema->_lauta[rivi][sarake+1] != nullptr) {
			if (asema->_lauta[rivi][sarake+1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake+1, rivi)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake+1, rivi)));
		}
	}

	if (sarake - 1 >= 0) {
		if (asema->_lauta[rivi][sarake-1] != nullptr) {
			if (asema->_lauta[rivi][sarake-1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi)));
		}
	}

	if (rivi + 1 <= 7 && sarake + 1 <= 7) {
		if (asema->_lauta[rivi + 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake + 1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi + 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi + 1)));
		}
	}

	if (rivi - 1 >= 0 && sarake + 1 <= 7) {
		if (asema->_lauta[rivi - 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake + 1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi - 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi - 1)));
		}
	}

	if (rivi + 1 <= 7 && sarake - 1 >= 0) {
		if (asema->_lauta[rivi + 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake - 1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi + 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi + 1)));
		}
	}

	if (rivi - 1 >= 0 && sarake - 1 >= 0) {
		if (asema->_lauta[rivi - 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake - 1]->getVari() != vari) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi - 1)));
			}
		}
		else {
			lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi - 1)));
		}
	}
}

void Sotilas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

	if (asema->getSiirtovuoro() != this->getVari()) return;
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (this->getVari() == 0) {
		// Valkoinen sotilas
		if (rivi - 1 >= 0) {
			if (asema->_lauta[rivi - 1][sarake] == nullptr) 
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 1)));
		}

		if (sarake + 1 <= 7 && rivi - 1 >= 0 && asema->_lauta[rivi - 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake + 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi - 1)));
		}

		if (sarake - 1 >= 0 && rivi - 1 >= 0 && asema->_lauta[rivi - 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake - 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi - 1)));
		}

		if (rivi == 6 && rivi - 2 >= 0) {
			if (asema->_lauta[rivi - 1][sarake] == nullptr && asema->_lauta[rivi - 2][sarake] == nullptr)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 2)));
		}
	}
	else {
		// Musta sotilas
		if (rivi + 1 <= 7) {
			if (asema->_lauta[rivi + 1][sarake] == nullptr)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi + 1)));
		}

		if (sarake + 1 <= 7 && rivi + 1 <= 7 && asema->_lauta[rivi + 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake + 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake + 1, rivi + 1)));
		}

		if (sarake - 1 >= 0 && rivi + 1 <= 7 && asema->_lauta[rivi + 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake - 1]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(sarake - 1, rivi + 1)));
		}

		if (rivi == 1 && rivi + 2 <= 7) {
			if (asema->_lauta[rivi + 1][sarake] == nullptr && asema->_lauta[rivi + 2][sarake] == nullptr) 
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi + 2)));
		}
	}
}

void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::vector<Siirto>& lista, Asema* asema) {
	
}
