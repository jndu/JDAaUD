#include "Obec.h"

bool Obec::patriDoVyssiehoCelku(const VyssiCelok& vyssiCelok) const
{
	return kodKraja_ == vyssiCelok.getKod() || kodOkresu_ == vyssiCelok.getKod();
}

int Obec::getKodKraja() const 
{ 
	return kodKraja_; 
}

std::string Obec::getNazovKraja() const 
{ 
	return nazovKraja_; 
}

int Obec::getKodOkresu() const 
{ 
	return kodOkresu_; 
}

std::string Obec::getNazovOkresu() const 
{ 
	return nazovOkresu_; 
}

void Obec::setKodKraja(int kodKraja) 
{ 
	kodKraja_ = kodKraja; 
}

void Obec::setNazovKraja(const std::string& nazovKraja) 
{ 
	nazovKraja_ = nazovKraja; 
}

void Obec::setKodOkresu(int kodOkresu) 
{ 
	kodOkresu_ = kodOkresu; 
}

void Obec::setNazovOkresu(const std::string& nazovOkresu)
{ 
	nazovOkresu_ = nazovOkresu; 
}