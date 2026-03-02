#pragma once

#include <string>
#include "asema.h"
#include "siirto.h"
using namespace std;

// Vakioarvot nappulatyypeille.
enum
{
	VT,VR,VL,VD,VK,VS,
	MT,MR,ML,MD,MK,MS
};

// Yliluokka shakkinappuloille.
class Nappula
{

private:
	wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int	_vari;		// valkea = 0, musta = 1
	int	_koodi;		// VT, VR, MT tms.
	int _arvo;
	wstring _nimi;

public:
	Nappula(wstring unicode, int vari, int koodi, int arvo);
	Nappula() {}

	// Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat t�m�n
	// omalla tavallaan.
	virtual void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari) = 0;

	void setUnicode(wstring unicode)		{ _unicode = unicode;			}
	void setKoodi(int koodi)				{ _koodi = koodi;				}
	void setVari(int vari)					{ _vari = vari;					}
	wstring getUnicode()					{ return _unicode;				}
	int getVari()							{ return _vari;					}
	int getArvo()							{ return _arvo;					}
	int getKoodi()							{ return _koodi;				}
	wstring getNimi()						{ return _nimi;					}
};

// Torni-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Torni : public virtual Nappula {
public:
	Torni(wstring unicode, int vari, int koodi, int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Ratsu-aliluokka.
class Ratsu : public Nappula {
public:
	Ratsu(wstring unicode, int vari, int koodi, int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// L�hetti-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Lahetti : public virtual Nappula {
public:
	Lahetti(std::wstring unicode, int vari, int koodi, int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Daami-aliluokka. Perii sek� l�hetin ett� tornin.
class Daami : public Lahetti, public Torni {
public:
	Daami(std::wstring unicode, int vari, int koodi, int arvo) :
		Nappula(unicode, vari, koodi, arvo), Lahetti(unicode, vari, koodi, arvo), Torni(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Kuningas-aliluokka.
class Kuningas : public Nappula {
public:
	Kuningas(wstring unicode, int vari, int koodi, int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Sotilas-aliluokka.
class Sotilas : public Nappula {
public:
	Sotilas(wstring unicode, int vari, int koodi, int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(vector<Siirto>& lista, Ruutu*, Asema*, int vari);
private:
	void lisaaSotilaanKorotukset(Siirto*, vector<Siirto>& lista, Asema*);
};


