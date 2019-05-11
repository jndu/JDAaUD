#pragma once

#include "Kolo.h"
#include "Kandidat.h"

enum class TypUzemnejJednotky { OBEC, OKRES, KRAJ };

class UzemnaJednotka
{
protected:
	UzemnaJednotka() = default;

	TypUzemnejJednotky typ_;

	int kod_;
	std::string nazov_;

	Kolo kolo1_;
	Kolo kolo2_;

public:
	virtual ~UzemnaJednotka() = default;

	int spocitajPocetZapisanychVolicovVKole(const TypKola kolo) const;
	int pocetVydanychObalokVKole(const TypKola kolo) const;
	double ucastVolicovVKole(const TypKola kolo) const;
	int pocetOdovzdanychObalokVKole(const TypKola kolo) const;
	int pocetZiskanychHlasovZaKandidata(const Kandidat& kandidat, const TypKola kolo) const;
	int pocetPlatnychHlasov(const TypKola kolo) const;

	TypUzemnejJednotky getTyp() const;
	int getKod() const;
	std::string getNazov() const;
	Kolo& getKolo1();
	Kolo& getKolo2();

	void setTyp(TypUzemnejJednotky typ);
	void setKod(int kod);
	void setNazov(std::string nazov);
};