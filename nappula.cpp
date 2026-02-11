#include <vector>
#include "nappula.h"

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}

void Torni::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	// if (asema->getSiirtovuoro() != this->getVari()) return;

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

void Ratsu::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

	// if (asema->getSiirtovuoro() != this->getVari()) return;
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

void Lahetti::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	// if (asema->getSiirtovuoro() != this->getVari()) return;

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
	for (int x = sarake - 1, y = rivi + 1; x >= 0 && y <= 7; x--, y++) {
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

void Daami::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}

void Kuningas::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.
	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/
	// if (asema->getSiirtovuoro() != this->getVari()) return;
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

void Sotilas::annaSiirrot(vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

	// if (asema->getSiirtovuoro() != this->getVari()) return;
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (this->getVari() == 0) {
		// Valkoinen sotilas
		
		if (rivi - 1 >= 0) {
			if (asema->_lauta[rivi - 1][sarake] == nullptr) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, rivi - 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
		}

		if (sarake + 1 <= 7 && rivi - 1 >= 0 && asema->_lauta[rivi - 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake + 1]->getVari() != vari) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake + 1, rivi - 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
				
		}

		if (sarake - 1 >= 0 && rivi - 1 >= 0 && asema->_lauta[rivi - 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi - 1][sarake - 1]->getVari() != vari) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake - 1, rivi - 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
				
		}

		if (rivi == 6 && rivi - 2 >= 0) {
			if (asema->_lauta[rivi - 1][sarake] == nullptr && asema->_lauta[rivi - 2][sarake] == nullptr) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, rivi - 2));
				lista.push_back(newSiirto);
			}
				
		}

		// en passant vasemmalle
		if (asema->kaksoisaskelSarakkeella == sarake - 1 && rivi == 3 && asema->_lauta[rivi - 1][sarake-1] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake - 1, rivi - 1));
			lista.push_back(newSiirto);
		}
		// en passant oikealle
		if (asema->kaksoisaskelSarakkeella == sarake + 1 && rivi == 3 && asema->_lauta[rivi - 1][sarake + 1] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake + 1, rivi - 1));
			lista.push_back(newSiirto);
		}

	}
	else {
		// Musta sotilas
		if (rivi + 1 <= 7) {
			if (asema->_lauta[rivi + 1][sarake] == nullptr) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, rivi + 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
				
		}

		if (sarake + 1 <= 7 && rivi + 1 <= 7 && asema->_lauta[rivi + 1][sarake + 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake + 1]->getVari() != vari) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake + 1, rivi + 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
		}

		if (sarake - 1 >= 0 && rivi + 1 <= 7 && asema->_lauta[rivi + 1][sarake - 1] != nullptr) {
			if (asema->_lauta[rivi + 1][sarake - 1]->getVari() != vari) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake - 1, rivi + 1));
				lista.push_back(newSiirto);
				lisaaSotilaanKorotukset(&newSiirto, lista, asema);
			}
		}

		if (rivi == 1 && rivi + 2 <= 7) {
			if (asema->_lauta[rivi + 1][sarake] == nullptr && asema->_lauta[rivi + 2][sarake] == nullptr) {
				Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake, rivi + 2));
				lista.push_back(newSiirto);
			}
		}

		// en passant vasemmalle
		if (asema->kaksoisaskelSarakkeella == sarake - 1 && rivi == 4 && asema->_lauta[rivi + 1][sarake - 1] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake - 1, rivi + 1));
			lista.push_back(newSiirto);
		}
		// en passant oikealle
		if (asema->kaksoisaskelSarakkeella == sarake + 1 && rivi == 4 && asema->_lauta[rivi + 1][sarake + 1] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(sarake + 1, rivi + 1));
			lista.push_back(newSiirto);
		}
	}
}

void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, vector<Siirto>& lista, Asema* asema) {
	if (this->getVari() == 1) { // Musta sotilas
		if (siirto->getLoppuruutu().getRivi() == 7) {
			Siirto mtSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::mt);
			lista.push_back(mtSiirto);
			Siirto mrSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::mr);
			lista.push_back(mrSiirto);
			Siirto mlSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::ml);
			lista.push_back(mlSiirto);
			Siirto mdSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::md);
			lista.push_back(mdSiirto);
		}
	} 
	else if (this->getVari() == 0) { // Valkoinen sotilas
		if (siirto->getLoppuruutu().getRivi() == 0) {
			Siirto vtSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::vt);
			lista.push_back(vtSiirto);
			Siirto vrSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::vr);
			lista.push_back(vrSiirto);
			Siirto vlSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::vl);
			lista.push_back(vlSiirto);
			Siirto vdSiirto = Siirto(siirto->getAlkuruutu(), siirto->getLoppuruutu(), Asema::vd);
			lista.push_back(vdSiirto);
		}
	}
}
