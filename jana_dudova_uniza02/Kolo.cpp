#include "Kolo.h"

int Kolo::getPocetZiskanychHlasovKandidat(int poradoveCislo) const 
{ 
	return pocetZiskanychHlasovKandidat_[poradoveCislo]; 
}

int Kolo::getPocetZapisanychVolicov() const
{ 
	return pocetZapisanychVolicov_; 
}

int Kolo::getPocetVydanychObalok() const 
{ 
	return pocetVydanychObalok_; 
}

double Kolo::getUcastVolicovPercent() const 
{ 
	return ucastVolicovPercent_; 
}

int Kolo::getPocetOdovzdanychObalok() const 
{ 
	return pocetOdovzdanychObalok_; 
}

double Kolo::getPodielOdovzdanychObalok() const 
{ 
	return podielOdovzdanychObalok_; 
}

int Kolo::getPocetPlatnychHlasovVsetkychKandidatov() const 
{ 
	return pocetPlatnychHlasovVsetkychKandidatov_; 
}

double Kolo::getPodielPlatnychHlasovVsetkychKandidatov() const 
{ 
	return podielPlatnychHlasovVsetkychKandidatov_; 
}

void Kolo::setPocetZiskanychHlasovKandidat(int poradoveCislo, int pocetZiskanychHlasov)
{
	if (pocetZiskanychHlasovKandidat_.containsKey(poradoveCislo))
	{
		pocetZiskanychHlasovKandidat_[poradoveCislo] = pocetZiskanychHlasov;
	}
	else
	{
		pocetZiskanychHlasovKandidat_.insert(poradoveCislo, pocetZiskanychHlasov);
	}
}
void Kolo::setPocetZapisanychVolicov(int pocetZapisanychVolicov) 
{
	pocetZapisanychVolicov_ = pocetZapisanychVolicov; 
}

void Kolo::setPocetVydanychObalok(int pocetVydanychObalok) 
{ 
	pocetVydanychObalok_ = pocetVydanychObalok; 
}

void Kolo::setUcastVolicovPercent(double ucastVolicovPercent) 
{
	ucastVolicovPercent_ = ucastVolicovPercent; 
}

void Kolo::setPocetOdovzdanychObalok(int pocetOdovzdanychObalok) 
{
	pocetOdovzdanychObalok_ = pocetOdovzdanychObalok; 
}

void Kolo::setPodielOdovzdanychObalok(double podielOdovzdanychObalok) 
{ 
	podielOdovzdanychObalok_ = podielOdovzdanychObalok; 
}

void Kolo::setPocetPlatnychHlasovVsetkychKandidatov(int pocetPlatnychHlasovVsetkychKandidatov) 
{ 
	pocetPlatnychHlasovVsetkychKandidatov_ = pocetPlatnychHlasovVsetkychKandidatov; 
}

void Kolo::setPodielPlatnychHlasovVsetkychKandidatov(double podielPlatnychHlasovVsetkychKandidatov) 
{ 
	podielPlatnychHlasovVsetkychKandidatov_ = podielPlatnychHlasovVsetkychKandidatov; 
}