#include "Kandidat.h"

int Kandidat::getPoradoveCislo1() const 
{ 
	return poradoveCislo1_; 
}

int Kandidat::getPoradoveCislo2() const 
{ 
	return poradoveCislo2_; 
}

std::string Kandidat::getMeno() const 
{ 
	return meno_; 
}

std::string Kandidat::getPiezvisko() const 
{ 
	return priezvisko_; 
}

std::string Kandidat::getCeleMeno() const 
{ 
	return meno_ + " " + priezvisko_; 
}

void Kandidat::setPoradoveCislo1(int poradoveCislo1) 
{ 
	poradoveCislo1_ = poradoveCislo1; 
}

void Kandidat::setPoradoveCislo2(int poradoveCislo2) 
{ 
	poradoveCislo2_ = poradoveCislo2; 
}

void Kandidat::setMeno(const std::string& meno) 
{
	meno_ = meno; 
}

void Kandidat::setPriezvisko(const std::string& priezvisko) 
{ 
	priezvisko_ = priezvisko; 
}