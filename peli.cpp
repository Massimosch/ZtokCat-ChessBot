#include "peli.h"

using namespace std;

Peli::Peli(int ihmisenVari)
{
	int vari = (ihmisenVari == 0) ? 1 : 0;
	_koneenVari = vari;
}


int Peli::getKoneenVari(){
	return _koneenVari;
}
