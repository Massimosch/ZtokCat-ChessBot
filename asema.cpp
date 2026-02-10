#include <iostream>
#include "asema.h"
#include "nappula.h"
#include "ruutu.h"
#include <list>
#include "kayttoliittyma.h"

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

	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoValkeaKuningasLiikkunut = false;

}


void Asema::paivitaAsema(Siirto *siirto)
{
	/*		{vs, vs, vs, vs, vs, vs, vs, vs},
		{vt, vr, vl, vd, vk, vl, vr, vt},*/
	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.

	kaksoisaskelSarakkeella = -1;
		
	if (siirto->onkoLyhytLinna()) { //Tarkastetaan on siirto lyhyt linna
		if (_siirtovuoro == 0) {
			//Torni
			_lauta[7][5] = vt;
			_lauta[7][7] = NULL;
			//Kunkku
			_lauta[7][6] = vk;
			_lauta[7][4] = NULL;
		}
		else {
			//MTorni
			_lauta[0][5] = mt;
			_lauta[0][7] = NULL;
			//MKunnkku
			_lauta[0][6] = mk;
			_lauta[0][7] = NULL;
		}
	}
	else if (siirto->onkoPitkalinna()) { 	// onko pitk� linna
		if (_siirtovuoro == 0) {
			//VTorni
			_lauta[7][3] = vt;
			_lauta[7][0] = NULL;
			//VKunkku
			_lauta[7][2] = vk;
			_lauta[7][4] = NULL;
		}
		else {
			_lauta[0][3] = mt;
			_lauta[0][0] = NULL;

			_lauta[0][2] = mk;
			_lauta[0][4] = NULL;
		}
	}
	else { // Kaikki muut siirrot
		Nappula* aloitusruudussanappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];
		Nappula* temp = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]; // Tallennetaan nykyinen nappula
		if (siirto->getMiksikorotetaan() != nullptr) temp = siirto->getMiksikorotetaan(); // korotus
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL; // Poistetaan nappula aloitusruudulta
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = temp; // siirretään nappula loppuruudulle

		// Jos sotilas liikkui kaksoisaskeleen, voi en passantaa
		if (aloitusruudussanappula == ms || aloitusruudussanappula == vs && abs(siirto->getAlkuruutu().getRivi() - siirto->getLoppuruutu().getRivi()) == 2) {
			kaksoisaskelSarakkeella = siirto->getLoppuruutu().getSarake();
		}

		// En passant
		if (aloitusruudussanappula == ms && _lauta[siirto->getLoppuruutu().getRivi() - 1][siirto->getLoppuruutu().getSarake()] == vs 
			&& _lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] == NULL) _lauta[siirto->getLoppuruutu().getRivi() - 1][siirto->getLoppuruutu().getSarake()] = NULL;
		if (aloitusruudussanappula == vs && _lauta[siirto->getLoppuruutu().getRivi() + 1][siirto->getLoppuruutu().getSarake()] == ms
			&& _lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] == NULL) _lauta[siirto->getLoppuruutu().getRivi() + 1][siirto->getLoppuruutu().getSarake()] = NULL;

		if (aloitusruudussanappula == mk) _onkoMustaKuningasLiikkunut = true;
		if (aloitusruudussanappula == mt && siirto->getAlkuruutu().getRivi() == 0
			&& siirto->getAlkuruutu().getSarake() == 0) _onkoMustaKTliikkunut = true;
		if (aloitusruudussanappula == mt && siirto->getAlkuruutu().getRivi() == 0
			&& siirto->getAlkuruutu().getSarake() == 7) _onkoMustaDTliikkunut = true;

		if (aloitusruudussanappula == vk) _onkoValkeaKuningasLiikkunut = true;
		if (aloitusruudussanappula == vt && siirto->getAlkuruutu().getRivi() == 7
			&& siirto->getAlkuruutu().getSarake() == 0) _onkoValkeaKTliikkunut = true;
		if (aloitusruudussanappula == vt && siirto->getAlkuruutu().getRivi() == 7
			&& siirto->getAlkuruutu().getSarake() == 7) _onkoValkeaDTliikkunut = true;
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
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return _onkoMustaKTliikkunut;
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

	//kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta
	double daami		= 9;
	double torni		= 5;
	double lahetti		= 3.25;
	double ratsu		= 3;
	double sotilas		= 1;
	//1. Nappuloiden arvo
	double valkean_arvo	= 0;
	double mustan_arvo	= 0;
	double arvo = 0;

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x <= 7; x++) {
			if (_lauta[y][x] == NULL) continue;
			if		(_lauta[y][x] == vd)	valkean_arvo += daami;
			else if (_lauta[y][x] == vt)	valkean_arvo += torni;
			else if (_lauta[y][x] == vl)	valkean_arvo += lahetti;
			else if (_lauta[y][x] == vr)	valkean_arvo += ratsu;
			else if (_lauta[y][x] == vs)	valkean_arvo += sotilas;

			else if (_lauta[y][x] == md)	mustan_arvo += daami;
			else if (_lauta[y][x] == mt)	mustan_arvo += torni;
			else if (_lauta[y][x] == ml)	mustan_arvo += lahetti;
			else if (_lauta[y][x] == mr)	mustan_arvo += ratsu;
			else if (_lauta[y][x] == ms)	mustan_arvo += sotilas;
		}
	}
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
	arvo = valkean_arvo - mustan_arvo;

	return arvo;
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
	vector<Siirto> lista;
	annaLaillisetSiirrot(lista);

	// Rekursion kantatapaus 1: peli on loppu
	if (lista.size() == 0) return paluuarvo;

	// Rekursion kantatapaus 2: katkaisusyvyydess�
	if (syvyys == 0) return paluuarvo;

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	for (Siirto siirto : lista) {
		if (_siirtovuoro == 0) paluuarvo = maxi(syvyys, *this);
		if (_siirtovuoro == 1) paluuarvo = mini(syvyys, *this);
	}

	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys, Asema a) 
{
	MinMaxPaluu paluu;
	if (syvyys == 0) return paluu;
	double max = -INFINITY;
	vector<Siirto> lista;
	a.annaLaillisetSiirrot(lista);
	for (Siirto siirto : lista) {
		a.paivitaAsema(&siirto);
		paluu._evaluointiArvo = a.evaluoi();
		if (paluu._evaluointiArvo > max) {
			paluu._parasSiirto = siirto;
			return paluu;
		}
		paluu = a.mini(syvyys - 1, a);
	}

	paluu._evaluointiArvo = max;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys, Asema a)
{
	MinMaxPaluu paluu;
	if (syvyys == 0) {
		paluu._evaluointiArvo = -paluu._evaluointiArvo;
		return paluu;
	}
	double min = +INFINITY;
	vector<Siirto> lista;
	a.annaLaillisetSiirrot(lista);
	for (Siirto siirto : lista) {
		a.paivitaAsema(&siirto);
		paluu._evaluointiArvo = a.evaluoi();
		if (paluu._evaluointiArvo < min) {
			paluu._parasSiirto = siirto;
			return paluu;
		}
		paluu = a.maxi(syvyys - 1, a);
	}
	paluu._evaluointiArvo = min;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::vector<Siirto> vastustajanSiirrot;

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x <= 7; x++) {
			if (_lauta[y][x] == NULL) continue;
			if (_lauta[y][x]->getVari() == vastustajanVari) _lauta[y][x]->annaSiirrot(vastustajanSiirrot, &Ruutu(x, y), this, vastustajanVari);
		}
	}

	for (auto siirto : vastustajanSiirrot) {
		if (ruutu->getSarake() == siirto.getLoppuruutu().getSarake() &&
			ruutu->getRivi() == siirto.getLoppuruutu().getRivi()) {
			return true;
		}
	}

	return false;
}

void Asema::annaLinnoitusSiirrot(vector<Siirto>& lista, int vari)
{
	if (vari == 0) { // Valkean linnoitukset
		// Lyhyt linnoitus
		if (!onkoRuutuUhattu(&Ruutu(4, 7), 1) && !onkoRuutuUhattu(&Ruutu(5, 7), 1) 
			&& !onkoRuutuUhattu(&Ruutu(6, 7), 1) && !getOnkoValkeaKTliikkunut() || !getOnkoValkeaKuningasLiikkunut()) {
			if (_lauta[7][5] == nullptr && _lauta[7][6] == nullptr) lista.push_back(Siirto(true, false));
		}
		// Pitkä linnoitus
		if (!onkoRuutuUhattu(&Ruutu(7, 4), 1) && !onkoRuutuUhattu(&Ruutu(7, 3), 1)
			&& !onkoRuutuUhattu(&Ruutu(7, 2), 1) && !getOnkoValkeaDTliikkunut() || !getOnkoValkeaKuningasLiikkunut()) {
			if (_lauta[7][3] == nullptr && _lauta[7][2] == nullptr && _lauta[7][1] == nullptr) lista.push_back(Siirto(false, true));
		}
	}
	else if (vari == 1) { // Mustan linnoitukset
		// Lyhyt linnoitus
		if (!onkoRuutuUhattu(&Ruutu(4, 0), 0) && !onkoRuutuUhattu(&Ruutu(5, 0), 0)
			&& !onkoRuutuUhattu(&Ruutu(6, 0), 0) && !getOnkoMustaKTliikkunut() || !getOnkoMustaKuningasLiikkunut()) {
			if (_lauta[0][5] == nullptr && _lauta[0][6] == nullptr) lista.push_back(Siirto(true, false));
		}
		// Pitkä linnoitus
		if (!onkoRuutuUhattu(&Ruutu(0, 4), 0) && !onkoRuutuUhattu(&Ruutu(0, 3), 0)
			&& !onkoRuutuUhattu(&Ruutu(0, 2), 1) && !getOnkoMustaDTliikkunut() || !getOnkoMustaKuningasLiikkunut()) {
			if (_lauta[0][3] == nullptr && _lauta[0][2] == nullptr && _lauta[0][1] == nullptr) lista.push_back(Siirto(false, true));
		}
	}
}


void Asema::huolehdiKuninkaanShakeista(vector<Siirto>& lista, int vari) 
{ 
	if (lista.size() == 0) return;

	int vastustaja = (vari == 0) ? 1 : 0;

	for (int i = lista.size() - 1; i >= 0; i--) {

		Siirto siirto = lista[i];
		Asema testi_asema = *this;
		testi_asema.paivitaAsema(&siirto);
		
		Ruutu kuningasruutu;
		for (int rivi = 0; rivi <= 7; rivi++) {
			for (int sarake = 0; sarake <= 7; sarake++) {
				if (testi_asema._lauta[rivi][sarake] == nullptr) continue;
				if ((testi_asema._lauta[rivi][sarake]->getKoodi() == VK && vari == 0)
					|| (testi_asema._lauta[rivi][sarake]->getKoodi() == MK && vari == 1)) {
					kuningasruutu = Ruutu(sarake, rivi);
					break;
				}
			}
			if (kuningasruutu.getRivi() <= 7 && kuningasruutu.getRivi() >= 0) break;
		}

		if (testi_asema.onkoRuutuUhattu(&kuningasruutu, vastustaja)) {
			lista.erase(lista.begin() + i);
		}
		

		//Ruutu alkuruutu = siirto.getAlkuruutu();
		//Ruutu kohde = siirto.getLoppuruutu();
		//if (!_lauta[alkuruutu.getRivi()][alkuruutu.getSarake()]) continue;
		//if (_lauta[alkuruutu.getRivi()][alkuruutu.getSarake()]->getKoodi() != MK 
		//	&& _lauta[alkuruutu.getRivi()][alkuruutu.getSarake()]->getKoodi() != VK) continue;
		//if (onkoRuutuUhattu(&kohde, vastustaja)) {
		//	lista.erase(lista.begin() + i);
		//	wcout << "Kuninkaalta poistettiin laiton siirto!" << endl;
		//}
	}
}


void Asema::annaLaillisetSiirrot(vector<Siirto>& lista) {
	for (int rivi = 0; rivi <= 7; rivi++) {
		for (int sarake = 0; sarake <= 7; sarake++) {
			if (_lauta[rivi][sarake] == nullptr) continue;
			if (_lauta[rivi][sarake]->getVari() != _siirtovuoro) continue;
			Ruutu* ruutu = &Ruutu(sarake, rivi);
			_lauta[rivi][sarake]->annaSiirrot(lista, ruutu, this, _siirtovuoro);
		}
	}
	//annaLinnoitusSiirrot(lista, _siirtovuoro);
	//huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}
