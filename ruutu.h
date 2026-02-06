#pragma once

// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.

class Ruutu{
public:
	Ruutu(int sarake, int rivi);
	Ruutu() {}
	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);
	bool operator == (const Ruutu& rhs);

private:
	int _sarake;
	int _rivi;
};
