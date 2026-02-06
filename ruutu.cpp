#include "ruutu.h"

// Laita ensin sarake, sitten rivi !!!!
Ruutu::Ruutu(int sarake, int rivi)
{
	_sarake = sarake;
	_rivi = rivi;
}

int Ruutu::getRivi()
{
	return _rivi;
}

int Ruutu::getSarake()
{
	return _sarake;
}

void Ruutu::setRivi(int rivi) 
{
	_rivi = rivi;
}

void Ruutu::setSarake(int sarake) 
{
	_sarake = sarake;
}

bool Ruutu::operator== (const Ruutu& rhs)
{
	return (this->_sarake == rhs._sarake) && (this->_rivi == rhs._rivi);
}
