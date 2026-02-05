#include <iostream>
#include "asema.h"
#include "nappula.h"
#include "ruutu.h"
#include <list>

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int x = 0; x <= 7; x++) {
		for (int y = 0; y <= 7; y++) {
			_lauta[x][y] = NULL;
		}
	}

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	Nappula* _aloituslauta[8][8] = {
		{mt, mr, ml, md, mk, ml, mr, mt},
		{ms, ms, ms, ms, ms, ms, ms, ms},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{vs, vs, vs, vs, vs, vs, vs, vs},
		{vt, vr, vl, vd, vk, vl, vr, vt},
	};

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			_lauta[i][j] = _aloituslauta[i][j];
		}
	}
}


void Asema::paivitaAsema(Siirto *siirto)
{
	/*		{vs, vs, vs, vs, vs, vs, vs, vs},
		{vt, vr, vl, vd, vk, vl, vr, vt},*/
	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.
	
		
	if (siirto->onkoLyhytLinna()) { //Tarkastetaan on siirto lyhyt linna
		if (_siirtovuoro == 0) {
			//Torni
			_lauta[0][5] = vt;
			_lauta[0][7] = NULL;
			//Kunkku
			_lauta[0][6] = vk;
			_lauta[0][4] = NULL;
		}
		else {
			//MTorni
			_lauta[7][5] = mt;
			_lauta[7][7] = NULL;
			//MKunnkku
			_lauta[7][6] = mk;
			_lauta[4][7] = NULL;
		}
	}
	else if (siirto->onkoPitkalinna()) { 	// onko pitk� linna
		if (_siirtovuoro == 0) {
			//VTorni
			_lauta[0][3] = vt;
			_lauta[0][0] = NULL;
			//VKunkku
			_lauta[0][2] = vk;
			_lauta[0][4] = NULL;
		}
		else {
			_lauta[7][3] = mt;
			_lauta[7][0] = NULL;

			_lauta[7][2] = mk;
			_lauta[7][4] = NULL;
		}
	}
	else { // Kaikki muut siirrot
		
		Nappula* temp = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]; // Tallennetaan nykyinen nappula
		if (siirto->getMiksikorotetaan() != nullptr) temp = siirto->getMiksikorotetaan(); // korotus
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL; // Poistetaan nappula aloitusruudulta
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = temp; // siirretään nappula loppuruudulle
	}

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)

		// Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula
		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)

	//p�ivitet��n _siirtovuoro
	int vuoro = (getSiirtovuoro()) ? 0 : 1;
	setSiirtovuoro(vuoro);
}



int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return false;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L�hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv� ett� kunigas g1 tai b1/c1
Loppupeliss� vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est�m�ss� vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki� linjoja daami, torni ja l�hetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai v�hemm�n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydess�
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::vector<Siirto> vastustajanSiirrot;

	bool uhattu { false };

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x <= 7; x++) {
			if (this->_lauta[y][x] == NULL)
				continue;
			if (this->_lauta[y][x]->getVari() == vastustajanVari)
				this->_lauta[y][x]->annaSiirrot(vastustajanSiirrot, &Ruutu(y, x), this, vastustajanVari);
		}
	}

	for (auto siirto : vastustajanSiirrot) {
		if (ruutu->getSarake() == siirto.getLoppuruutu().getSarake() &&
			ruutu->getRivi() == siirto.getLoppuruutu().getRivi()) {
			uhattu = true;
			break;
		}
	}

	return uhattu;
}

void Asema::annaLinnoitusSiirrot(vector<Siirto>& lista, int vari)
{

}


void Asema::huolehdiKuninkaanShakeista(vector<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(vector<Siirto>& lista) {
	for (int rivi = 0; rivi <= 7; rivi++) {
		for (int sarake = 0; sarake <= 7; sarake++) {
			if (_lauta[rivi][sarake] == nullptr) continue;
			Ruutu* ruutu = &Ruutu(sarake, rivi);
			_lauta[rivi][sarake]->annaSiirrot(lista, ruutu, this, _siirtovuoro);
		}
	}
}
