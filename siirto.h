#pragma once
#include "ruutu.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell� Nappula-osoittimia ilman,
// ett� nappula.h -tiedostoa t�ytyy includoida.
class Nappula; 


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestaly�nti).
class Siirto {
public:
	Siirto(Ruutu, Ruutu);
	Siirto(Ruutu, Ruutu, Nappula* miksikorotetaan);
	Siirto();
	Siirto(bool lyhytLinna, bool pitkaLinna); // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	int getJarjestysArvo() { return jarjestys_arvo; }
	void setJarjestysArvo(int arvo) { jarjestys_arvo = arvo; }
	bool onkoLyhytLinna();
	bool onkoPitkalinna();
	Nappula* getMiksikorotetaan();
	bool operator== (const Siirto& rhs);
	bool operator< (const Siirto& rhs);

private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	Nappula* _miksikorotetaan = 0;
	int jarjestys_arvo = 0;
	bool _lyhytLinna;
	bool _pitkaLinna;
};