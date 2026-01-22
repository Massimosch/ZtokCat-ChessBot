#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}

void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	// Oikealle
	for (int x = rivi+1; x <= 7; x++) {
		if (asema->_lauta[x][sarake] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[x][sarake]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[x][sarake]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
		lista.push_back(newSiirto);
	}

	// Vasemmalle
	for (int x = rivi-1; x >= 0; x--) {
		if (asema->_lauta[x][sarake] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[x][sarake]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[x][sarake]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(x, sarake));
		lista.push_back(newSiirto);
	}

	// Ylös
	for (int y = sarake+1; y <= 7; y++) {
		if (asema->_lauta[rivi][y] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[rivi][y]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[rivi][y]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
		lista.push_back(newSiirto);
	}

	// Alas
	for (int y = sarake-1; y >= 0; y--) {
		if (asema->_lauta[rivi][y] == nullptr) {
			Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
			lista.push_back(newSiirto);
			continue;
		}
		if (asema->_lauta[rivi][y]->getVari() == vari) break; // oma nappula
		if (asema->_lauta[rivi][y]->getVari() != vari) {		// vastustajan nappula
			Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
			lista.push_back(newSiirto);
			break;
		}
		// ei nappulaa
		Siirto newSiirto = Siirto(*ruutu, Ruutu(rivi, y));
		lista.push_back(newSiirto);
	}
}

void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
}

void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
}

void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
}

void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.
	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/

	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	return;
	if (asema->_lauta[rivi + 1][sarake]->getVari() != vari) {
		
	}
	else {
		return;
	}

	if (asema->_lauta[rivi - 1][sarake]->getVari() != vari) {

	}

	if (asema->_lauta[rivi][sarake + 1]->getVari() != vari) {

	}

	if (asema->_lauta[rivi][sarake - 1]->getVari() != vari) {

	}

	if (asema->_lauta[rivi + 1][sarake -1]->getVari() != vari) {

	}

	if (asema->_lauta[rivi - 1][sarake - 1]->getVari() != vari) {

	}

	if (asema->_lauta[rivi + 1][sarake + 1]->getVari() != vari) {

	}


}

void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
}

void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
