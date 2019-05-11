#include "Okres.h"

int Okres::getKodKraja() const 
{ 
	return kodKraja_; 
}

std::string Okres::getNazovKraja() const
{ 
	return nazovKraja_; 
}

void Okres::setKodKraja(int kodKraja)
{ 
	kodKraja_ = kodKraja; 
}

void Okres::setNazovKraja(const std::string& nazovKraja)
{
	nazovKraja_ = nazovKraja; 
}