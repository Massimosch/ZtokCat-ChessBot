#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu, bool sieppausSiirto)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_miksikorotetaan = nullptr;
	_lyhytLinna = false;
	_pitkaLinna = false;
	_sieppausSiirto = sieppausSiirto;
}

Siirto::Siirto() {
	_loppuRuutu = Ruutu(-1, -1); 
	_alkuRuutu = Ruutu(-1, -1); 
	_lyhytLinna = false;
	_pitkaLinna = false;
	_sieppausSiirto = false;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) 
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
}

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu, Nappula* miksikorotetaan, bool sieppausSiirto) {
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_lyhytLinna = false;
	_pitkaLinna = false;
	_miksikorotetaan = miksikorotetaan;
	_sieppausSiirto = sieppausSiirto;
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

bool Siirto::operator== (const Siirto& rhs)
{
	return ((this->_alkuRuutu == rhs._alkuRuutu) && (this->_loppuRuutu == rhs._loppuRuutu)) || (this->_lyhytLinna == rhs._lyhytLinna) || (this->_pitkaLinna == rhs._pitkaLinna);
}

bool Siirto::operator< (const Siirto& rhs) {
	return (this->jarjestys_arvo < rhs.jarjestys_arvo);
}
