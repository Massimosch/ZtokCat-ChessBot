#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"

// LIGHTTILE colors
#define LIGHTTILE_BLUE       0x0001
#define LIGHTTILE_GREEN       0x0002
#define LIGHTTILE_RED         0x0004
#define LIGHTTILE_INTENSITY   0x0008  // makes it brighter

// DARKTILE colors
#define DARKTILE_BLUE        0x0010
#define DARKTILE_GREEN       0x0020
#define DARKTILE_RED         0x0040
#define DARKTILE_INTENSITY   0x0080  // brighter background

// Shakkiohjelman käyttöliittymä, joka osaa visualisoida nykyisen aseman
// ja lukea käyttäjän syöttämät siirrot. Singleton.
class Kayttoliittyma
{
public:

	void aseta_asema(Asema* asema) { this->_asema = asema;  }
	void piirraLauta();
	Siirto annaVastustajanSiirto();
	int kysyVastustajanVari();

	static Kayttoliittyma* getInstance();

private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).

	Kayttoliittyma() {}
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};
