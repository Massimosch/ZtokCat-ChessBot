#pragma once
#include <string>
using namespace std;

// Vastustajan tiedot.
class Vastustaja
{
public:
	Vastustaja(wstring nimimerkki);
	wstring getNimimerkki();

private:
	wstring _nimimerkki;
};
