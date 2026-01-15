#include "laillisetSiirrot.h"
#include "pelipuu.h"
// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
//int maxi(int depth, asema a) {
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

MinMaxPaluu Pelipuu::maxi(int syvyys, Asema* asema) {
	LaillisetSiirrot lailliset;
	std::list<Siirto> lista;
	Ruutu kuninkaanRuutu;
	lailliset.annaLaillisetSiirrot(asema, lista);
	double arvo;
	Asema uusiAsema;
	Siirto parasSiirto;
	MinMaxPaluu paluu;
	// Tarkasta onko matti tai patti, jos on niin poistu asap, matti -100000, patti 0
	if (lista.size() == 0) {
		//selvit� kuninkaan ruutu
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (asema->_lauta[x][y] != NULL) {
					if (asema->_lauta[x][y]->getNimi() == L"vk") {
						kuninkaanRuutu.setSarake(x);
						kuninkaanRuutu.setRivi(y);
					}
				}
			}
		}
		//matti
		if (lailliset.onkoRuutuUhattu(&kuninkaanRuutu, asema, 1)) {
			paluu._evaluointiArvo = -1000000;
			return paluu;
		}
		//patti
		if (!lailliset.onkoRuutuUhattu(&kuninkaanRuutu, asema, 1)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	// Jos ei ole matti tai patti niin k�y pelipuuta l�pi rekursiivisesti
	if (syvyys == 0) { // rekursion kanta
		paluu._evaluointiArvo = asema->evaluoi();
		return 	paluu;
	}
	double maximi = -100000; // iso arvo jotta varmasti paranee
	for (auto s : lista) {
		uusiAsema = *asema;
		uusiAsema.paivitaAsema(&s);
			arvo = mini(syvyys - 1, &uusiAsema)._evaluointiArvo;
			if (arvo > maximi) {
				maximi = arvo;
				parasSiirto = s;
			}
	}
	paluu._evaluointiArvo = maximi;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}


MinMaxPaluu Pelipuu::mini(int syvyys, Asema* asema) {
	LaillisetSiirrot lailliset;
	std::list<Siirto> lista;
	Ruutu kuninkaanRuutu;
	lailliset.annaLaillisetSiirrot(asema, lista);
	double arvo;
	Asema uusiAsema;
	Siirto parasSiirto;
	MinMaxPaluu paluu;
	// Tarkasta onko matti tai patti, jos on niin poistu asap, matti -100000, patti 0
	if (lista.size() == 0) {
		//selvit� kuninkaan ruutu
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (asema->_lauta[x][y] != NULL) {
					if (asema->_lauta[x][y]->getNimi() == L"mk") {
						kuninkaanRuutu.setSarake(x);
						kuninkaanRuutu.setRivi(y);
					}
				}
			}
		}
		//matti
		if (lailliset.onkoRuutuUhattu(&kuninkaanRuutu, asema, 0)) {
			paluu._evaluointiArvo = 1000000;
			return paluu;
		}
		//patti
		if (!lailliset.onkoRuutuUhattu(&kuninkaanRuutu, asema, 0)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	// Jos ei ole matti tai patti niin k�y pelipuuta l�pi rekursiivisesti
	if (syvyys == 0) { // rekursion kanta
		paluu._evaluointiArvo = asema->evaluoi();
		//paluu.parasSiirto = MIT�
		return 	paluu;
	}
	double minimi = 100000; // iso arvo jotta varmasti paranee
	for (auto s : lista) {
		uusiAsema = *asema;
		uusiAsema.paivitaAsema(&s);
		arvo = maxi(syvyys - 1, &uusiAsema)._evaluointiArvo;
		if (arvo < minimi) {
			minimi = arvo;
			parasSiirto = s;
		}
	}
	paluu._evaluointiArvo = minimi;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}
