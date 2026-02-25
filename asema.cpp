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


int mg_pawn_table[64] = {
	  0,   0,   0,   0,   0,   0,  0,   0,
	 98, 134,  61,  95,  68, 126, 34, -11,
	 -6,   7,  26,  31,  65,  56, 25, -20,
	-14,  13,   6,  21,  23,  12, 17, -23,
	-27,  -2,  -5,  12,  17,   6, 10, -25,
	-26,  -4,  -4, -10,   3,   3, 33, -12,
	-35,  -1, -20, -23, -15,  24, 38, -22,
	  0,   0,   0,   0,   0,   0,  0,   0,
};

int eg_pawn_table[64] = {
	  0,   0,   0,   0,   0,   0,   0,   0,
	178, 173, 158, 134, 147, 132, 165, 187,
	 94, 100,  85,  67,  56,  53,  82,  84,
	 32,  24,  13,   5,  -2,   4,  17,  17,
	 13,   9,  -3,  -7,  -7,  -8,   3,  -1,
	  4,   7,  -6,   1,   0,  -5,  -1,  -8,
	 13,   8,   8,  10,  13,   0,   2,  -7,
	  0,   0,   0,   0,   0,   0,   0,   0,
};

int mg_knight_table[64] = {
	-167, -89, -34, -49,  61, -97, -15, -107,
	 -73, -41,  72,  36,  23,  62,   7,  -17,
	 -47,  60,  37,  65,  84, 129,  73,   44,
	  -9,  17,  19,  53,  37,  69,  18,   22,
	 -13,   4,  16,  13,  28,  19,  21,   -8,
	 -23,  -9,  12,  10,  19,  17,  25,  -16,
	 -29, -53, -12,  -3,  -1,  18, -14,  -19,
	-105, -21, -58, -33, -17, -28, -19,  -23,
};

int eg_knight_table[64] = {
	-58, -38, -13, -28, -31, -27, -63, -99,
	-25,  -8, -25,  -2,  -9, -25, -24, -52,
	-24, -20,  10,   9,  -1,  -9, -19, -41,
	-17,   3,  22,  22,  22,  11,   8, -18,
	-18,  -6,  16,  25,  16,  17,   4, -18,
	-23,  -3,  -1,  15,  10,  -3, -20, -22,
	-42, -20, -10,  -5,  -2, -20, -23, -44,
	-29, -51, -23, -15, -22, -18, -50, -64,
};

int mg_bishop_table[64] = {
	-29,   4, -82, -37, -25, -42,   7,  -8,
	-26,  16, -18, -13,  30,  59,  18, -47,
	-16,  37,  43,  40,  35,  50,  37,  -2,
	 -4,   5,  19,  50,  37,  37,   7,  -2,
	 -6,  13,  13,  26,  34,  12,  10,   4,
	  0,  15,  15,  15,  14,  27,  18,  10,
	  4,  15,  16,   0,   7,  21,  33,   1,
	-33,  -3, -14, -21, -13, -12, -39, -21,
};

int eg_bishop_table[64] = {
	-14, -21, -11,  -8, -7,  -9, -17, -24,
	 -8,  -4,   7, -12, -3, -13,  -4, -14,
	  2,  -8,   0,  -1, -2,   6,   0,   4,
	 -3,   9,  12,   9, 14,  10,   3,   2,
	 -6,   3,  13,  19,  7,  10,  -3,  -9,
	-12,  -3,   8,  10, 13,   3,  -7, -15,
	-14, -18,  -7,  -1,  4,  -9, -15, -27,
	-23,  -9, -23,  -5, -9, -16,  -5, -17,
};

int mg_rook_table[64] = {
	 32,  42,  32,  51, 63,  9,  31,  43,
	 27,  32,  58,  62, 80, 67,  26,  44,
	 -5,  19,  26,  36, 17, 45,  61,  16,
	-24, -11,   7,  26, 24, 35,  -8, -20,
	-36, -26, -12,  -1,  9, -7,   6, -23,
	-45, -25, -16, -17,  3,  0,  -5, -33,
	-44, -16, -20,  -9, -1, 11,  -6, -71,
	-19, -13,   1,  17, 16,  7, -37, -26,
};

int eg_rook_table[64] = {
	13, 10, 18, 15, 12,  12,   8,   5,
	11, 13, 13, 11, -3,   3,   8,   3,
	 7,  7,  7,  5,  4,  -3,  -5,  -3,
	 4,  3, 13,  1,  2,   1,  -1,   2,
	 3,  5,  8,  4, -5,  -6,  -8, -11,
	-4,  0, -5, -1, -7, -12,  -8, -16,
	-6, -6,  0,  2, -9,  -9, -11,  -3,
	-9,  2,  3, -1, -5, -13,   4, -20,
};

int mg_queen_table[64] = {
	-28,   0,  29,  12,  59,  44,  43,  45,
	-24, -39,  -5,   1, -16,  57,  28,  54,
	-13, -17,   7,   8,  29,  56,  47,  57,
	-27, -27, -16, -16,  -1,  17,  -2,   1,
	 -9, -26,  -9, -10,  -2,  -4,   3,  -3,
	-14,   2, -11,  -2,  -5,   2,  14,   5,
	-35,  -8,  11,   2,   8,  15,  -3,   1,
	 -1, -18,  -9,  10, -15, -25, -31, -50,
};

int eg_queen_table[64] = {
	 -9,  22,  22,  27,  27,  19,  10,  20,
	-17,  20,  32,  41,  58,  25,  30,   0,
	-20,   6,   9,  49,  47,  35,  19,   9,
	  3,  22,  24,  45,  57,  40,  57,  36,
	-18,  28,  19,  47,  31,  34,  39,  23,
	-16, -27,  15,   6,   9,  17,  10,   5,
	-22, -23, -30, -16, -16, -23, -36, -32,
	-33, -28, -22, -43,  -5, -32, -20, -41,
};

int mg_king_table[64] = {
	-65,  23,  16, -15, -56, -34,   2,  13,
	 29,  -1, -20,  -7,  -8,  -4, -38, -29,
	 -9,  24,   2, -16, -20,   6,  22, -22,
	-17, -20, -12, -27, -30, -25, -14, -36,
	-49,  -1, -27, -39, -46, -44, -33, -51,
	-14, -14, -22, -46, -44, -30, -15, -27,
	  1,   7,  -8, -64, -43, -16,   9,   8,
	-15,  36,  12, -54,   8, -28,  24,  14,
};

int eg_king_table[64] = {
	-74, -35, -18, -18, -11,  15,   4, -17,
	-12,  17,  14,  17,  17,  38,  23,  11,
	 10,  17,  23,  15,  20,  45,  44,  13,
	 -8,  22,  24,  27,  26,  33,  26,   3,
	-18,  -4,  21,  24,  27,  23,   9, -11,
	-19,  -3,  11,  21,  23,  16,   7,  -9,
	-27, -11,   4,  13,  14,   4,  -5, -17,
	-53, -34, -21, -11, -28, -14, -24, -43
};

int* mg_pesto_table[6] =
{
	mg_pawn_table,
	mg_knight_table,
	mg_bishop_table,
	mg_rook_table,
	mg_queen_table,
	mg_king_table
};

int* eg_pesto_table[6] =
{
	eg_pawn_table,
	eg_knight_table,
	eg_bishop_table,
	eg_rook_table,
	eg_queen_table,
	eg_king_table
};

int gamephaseInc[12] = { 0,0,1,1,1,1,2,2,4,4,0,0 };

int mg_value[6] = { 82, 337, 365, 477, 1025,  0 };
int eg_value[6] = { 94, 281, 297, 512,  936,  0 };
int mg_table[12][64];
int eg_table[12][64];

#define PAWN   0
#define KNIGHT 1
#define BISHOP 2
#define ROOK   3
#define QUEEN  4
#define KING   5

/* board representation */
#define WHITE  0
#define BLACK  1

#define WHITE_PAWN      (2*PAWN   + WHITE)
#define BLACK_PAWN      (2*PAWN   + BLACK)
#define WHITE_KNIGHT    (2*KNIGHT + WHITE)
#define BLACK_KNIGHT    (2*KNIGHT + BLACK)
#define WHITE_BISHOP    (2*BISHOP + WHITE)
#define BLACK_BISHOP    (2*BISHOP + BLACK)
#define WHITE_ROOK      (2*ROOK   + WHITE)
#define BLACK_ROOK      (2*ROOK   + BLACK)
#define WHITE_QUEEN     (2*QUEEN  + WHITE)
#define BLACK_QUEEN     (2*QUEEN  + BLACK)
#define WHITE_KING      (2*KING   + WHITE)
#define BLACK_KING      (2*KING   + BLACK)
#define EMPTY           (BLACK_KING  +  1)

#define PCOLOR(p) ((p)&1)

int side2move;
int board[64];

#define FLIP(sq) ((sq)^56)
#define OTHER(side) ((side)^ 1)

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

	int pc, p, sq;
	for (p = PAWN, pc = WHITE_PAWN; p <= KING; pc += 2, p++) {
		for (sq = 0; sq < 64; sq++) {
			mg_table[pc][sq] = mg_value[p] + mg_pesto_table[p][sq];
			eg_table[pc][sq] = eg_value[p] + eg_pesto_table[p][sq];
			mg_table[pc + 1][sq] = mg_value[p] + mg_pesto_table[p][FLIP(sq)];
			eg_table[pc + 1][sq] = eg_value[p] + eg_pesto_table[p][FLIP(sq)];
		}
	}
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

	//1. Nappuloiden arvo
	int arvo = laskeNappuloidenArvo(0);

	//double nappula_arvo = laskeNappuloidenArvo(_siirtovuoro);
	//2. Kuningas turvassa

	//3. Arvosta keskustaa

	// 4. Arvosta linjoja
	return arvo;
}

double Asema::laskeNappuloidenArvo(int vari) 
{
	double valkea_arvo = 0;
	double musta_arvo = 0;
	int sq = 0;
	for (int rivi = 0; rivi <= 7; rivi++, sq++) {
		for (int sarake = 0; sarake <= 7; sarake++, sq++) {
			Nappula* pc = _lauta[rivi][sarake];
			if (pc != nullptr) {
				int nappula;
				if (pc == vs) nappula = WHITE_PAWN;
				else if (pc == ms) nappula = BLACK_PAWN;
				else if (pc == vr) nappula = WHITE_KNIGHT;
				else if (pc == mr) nappula = BLACK_KNIGHT;
				else if (pc == vl) nappula = WHITE_BISHOP;
				else if (pc == ml) nappula = BLACK_BISHOP;
				else if (pc == vt) nappula = WHITE_ROOK;
				else if (pc == mt) nappula = BLACK_ROOK;
				else if (pc == vd) nappula = WHITE_QUEEN;
				else if (pc == md) nappula = BLACK_QUEEN;
				else if (pc == vk) nappula = WHITE_KING;
				else if (pc == mk) nappula = BLACK_KING;
				if (pc->getVari() == 0 )	musta_arvo += mg_table[nappula][sq];
				else						valkea_arvo += eg_table[nappula][sq];
			}
		}
	}
	double arvo = (musta_arvo + valkea_arvo) / 24;
	if (arvo < -2000 || arvo > 2000) wcout << "Jotain meni pieleen";
	return arvo;
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

MinMaxPaluu Asema::minimax(int alpha, int beta, int syvyys)
{
	MinMaxPaluu paluuarvo;
	// Generoidaan aseman lailliset siirrot.
	vector<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	// Rekursion kantatapaus 1: peli on loppu
	if (siirrot.size() == 0) {
		// katso onko kuningas uhattu jos joo niin peli palauttaa äärettömän suuren arvon
		Ruutu kuningasruutu;
		for (int rivi = 0; rivi <= 7; rivi++) {
			for (int sarake = 0; sarake <= 7; sarake++) {
				if (_lauta[rivi][sarake] == nullptr) continue;
				if ((_lauta[rivi][sarake] == vk && _siirtovuoro == 0) || (_lauta[rivi][sarake] == mk && _siirtovuoro == 1)) {
					kuningasruutu = Ruutu(sarake, rivi);
					break;
				}
			}
		}
		int vastustajan_vari = (_siirtovuoro == 0) ? 1 : 0;
		if (onkoRuutuUhattu(&kuningasruutu, vastustajan_vari)) {
			paluuarvo._evaluointiArvo = 1000000;
			return paluuarvo;
		}
		paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}
	// Rekursion kantatapaus 2: katkaisusyvyydess�
	if (syvyys == 0) {
		paluuarvo._evaluointiArvo = this->evaluoi();
		if (paluuarvo._evaluointiArvo < -2000 || paluuarvo._evaluointiArvo > 2000) wcout << "Jotain meni pieleen";
		return paluuarvo;
	}
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	double mini = 100000000;
	double maxi = -100000000;
	for (Siirto s : siirrot) {
		
		Asema testi_asema = *this;
		testi_asema.paivitaAsema(&s);

		double arvo = testi_asema.minimax(alpha, beta, syvyys - 1)._evaluointiArvo;

		//wcout << " Arvo: " << arvo << endl;
		//Kayttoliittyma::getInstance()->piirraLauta(&testi_asema);

		if (_siirtovuoro == 0 && arvo > maxi) {
			paluuarvo._parasSiirto = s;
			paluuarvo._evaluointiArvo = arvo;
			maxi = arvo;
			if (arvo > alpha) alpha = arvo;
		}
		else if (_siirtovuoro == 1 && arvo < mini) {
			paluuarvo._parasSiirto = s;
			paluuarvo._evaluointiArvo = arvo;
			mini = arvo;
		}

		if (_siirtovuoro == 0 && arvo >= beta) return paluuarvo;
		if (_siirtovuoro == 1 && arvo <= alpha) return paluuarvo;

	}
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
				if ((testi_asema._lauta[rivi][sarake]->getKoodi() == VK && vari == 0) || (testi_asema._lauta[rivi][sarake]->getKoodi() == MK && vari == 1)) {
					kuningasruutu = Ruutu(sarake, rivi);
					break;
				}
			}
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
	annaLinnoitusSiirrot(lista, _siirtovuoro);
	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}
