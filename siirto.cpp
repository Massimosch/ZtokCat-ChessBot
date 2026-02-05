#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_miksikorotetaan = nullptr;
	_lyhytLinna = false;
	_pitkaLinna = false;
}

Siirto::Siirto() {
	_loppuRuutu = Ruutu(-1, -1); 
	_alkuRuutu = Ruutu(-1, -1); 
	_lyhytLinna = false;
	_pitkaLinna = false;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) 
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
}

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu, Nappula* miksikorotetaan) {
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_lyhytLinna = false;
	_pitkaLinna = false;
	_miksikorotetaan = miksikorotetaan;
}

Ruutu Siirto::getAlkuruutu()
{
	return _alkuRuutu;
}

Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}


bool Siirto::onkoLyhytLinna() 
{
	return _lyhytLinna;
}

bool Siirto::onkoPitkalinna() 
{
	return _pitkaLinna;
}

Nappula* Siirto::getMiksikorotetaan() {
	return _miksikorotetaan;
}
