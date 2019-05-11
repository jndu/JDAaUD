#include "UzemnaJednotka.h"

int UzemnaJednotka::spocitajPocetZapisanychVolicovVKole(const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getPocetZapisanychVolicov();
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getPocetZapisanychVolicov();
	}
	else
	{
		return kolo1_.getPocetZapisanychVolicov() + kolo2_.getPocetZapisanychVolicov();
	}
}

int UzemnaJednotka::pocetVydanychObalokVKole(const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getPocetVydanychObalok();
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getPocetVydanychObalok();
	}
	else
	{
		return kolo1_.getPocetVydanychObalok() + kolo2_.getPocetVydanychObalok();
	}
}

double UzemnaJednotka::ucastVolicovVKole(const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getUcastVolicovPercent();
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getUcastVolicovPercent();
	}
	else
	{
		return kolo1_.getUcastVolicovPercent() + kolo2_.getUcastVolicovPercent();
	}
}

int UzemnaJednotka::pocetOdovzdanychObalokVKole(const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getPocetOdovzdanychObalok();
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getPocetOdovzdanychObalok();
	}
	else
	{
		return kolo1_.getPocetOdovzdanychObalok() + kolo2_.getPocetOdovzdanychObalok();
	}
}

int UzemnaJednotka::pocetZiskanychHlasovZaKandidata(const Kandidat& kandidat, const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getPocetZiskanychHlasovKandidat(kandidat.getPoradoveCislo1());
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getPocetZiskanychHlasovKandidat(kandidat.getPoradoveCislo2());
	}
	else
	{
		return kolo1_.getPocetZiskanychHlasovKandidat(kandidat.getPoradoveCislo1()) + kolo2_.getPocetZiskanychHlasovKandidat(kandidat.getPoradoveCislo2());
	}
}

int UzemnaJednotka::pocetPlatnychHlasov(const TypKola kolo) const
{
	if (kolo == TypKola::PRVE)
	{
		return kolo1_.getPocetPlatnychHlasovVsetkychKandidatov();
	}
	else if (kolo == TypKola::DRUHE)
	{
		return kolo2_.getPocetPlatnychHlasovVsetkychKandidatov();
	}
	else
	{
		return kolo1_.getPocetPlatnychHlasovVsetkychKandidatov() + kolo2_.getPocetPlatnychHlasovVsetkychKandidatov();
	}
}

TypUzemnejJednotky UzemnaJednotka::getTyp() const 
{ 
	return typ_; 
}

int UzemnaJednotka::getKod() const 
{ 
	return kod_; 
}

std::string UzemnaJednotka::getNazov() const 
{ 
	return nazov_; 
}

Kolo& UzemnaJednotka::getKolo1() 
{ 
	return kolo1_; 
}

Kolo& UzemnaJednotka::getKolo2()
{ 
	return kolo2_; 
}

void UzemnaJednotka::setTyp(TypUzemnejJednotky typ)
{ 
	typ_ = typ; 
}

void UzemnaJednotka::setKod(int kod) 
{ 
	kod_ = kod; 
}

void UzemnaJednotka::setNazov(std::string nazov) 
{
	nazov_ = nazov; 
}