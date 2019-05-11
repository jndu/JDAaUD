#pragma once

#include "Kandidat.h"
#include "UzemnaJednotka.h"
#include "VyssiCelok.h"
#include "Obec.h"

template<typename T, typename O>
class Kriterium
{
private:
public:
	virtual ~Kriterium() = default;
	virtual T evaluate(const O& object) const = 0;
};

class KriteriumNazov : public Kriterium<std::string, UzemnaJednotka>
{
private:
public:
	std::string evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.getNazov();
	}
};

class KriteriumPrislusnostObce : public Kriterium<bool, Obec>
{
private:
	const VyssiCelok& vyssiCelok_;
public:
	KriteriumPrislusnostObce(const VyssiCelok& vyssiCelok) : vyssiCelok_(vyssiCelok) {}

	bool evaluate(const Obec& obec) const override
	{
		return obec.patriDoVyssiehoCelku(vyssiCelok_);
	}
};

class KriteriumVolici : public Kriterium<int, UzemnaJednotka>
{
private:
	const TypKola kolo_;
public:
	KriteriumVolici(const TypKola typKola) : kolo_(typKola) {}

	int evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.spocitajPocetZapisanychVolicovVKole(kolo_);
	}
};

class KriteriumVydaneObalky : public Kriterium<int, UzemnaJednotka>
{
private:
	const TypKola kolo_;
public:
	KriteriumVydaneObalky(const TypKola typKola) : kolo_(typKola) {}

	int evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.pocetVydanychObalokVKole(kolo_);
	}
};

class KriteriumUcast : public Kriterium<double, UzemnaJednotka>
{
private:
	const TypKola kolo_;
public:
	KriteriumUcast(const TypKola typKola) : kolo_(typKola) {}

	double evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.ucastVolicovVKole(kolo_);
	}
};

class KriteriumOdovzdaneObalky : public Kriterium<int, UzemnaJednotka>
{
private:
	const TypKola kolo_;
public:
	KriteriumOdovzdaneObalky(const TypKola typKola) : kolo_(typKola) {}

	int evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.pocetOdovzdanychObalokVKole(kolo_);
	}
};

class KriteriumHlasyOdovzdane : public Kriterium<int, UzemnaJednotka>
{
private:
	const Kandidat& kandidat_;
	const TypKola kolo_;
public:
	KriteriumHlasyOdovzdane(const Kandidat& kandidat, const TypKola kolo) : kandidat_(kandidat), kolo_(kolo) {}

	int evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.pocetZiskanychHlasovZaKandidata(kandidat_, kolo_);
	}
};

class KriteriumMeno : public Kriterium<std::string, Kandidat>
{
public:
	std::string evaluate(const Kandidat& kandidat) const override
	{
		return kandidat.getCeleMeno();
	}
};

class KriteriumHlasyZiskane : public Kriterium<int, Kandidat>
{
private:
	const UzemnaJednotka& uzemnaJednotka_;
	const TypKola kolo_;
public:
	KriteriumHlasyZiskane(const UzemnaJednotka& uzemnaJednotka, const TypKola typKola) : uzemnaJednotka_(uzemnaJednotka), kolo_(typKola) {}

	int evaluate(const Kandidat& kandidat) const override
	{
		return uzemnaJednotka_.pocetZiskanychHlasovZaKandidata(kandidat, kolo_);
	}
};

// novy kvoli 1)
class KriteriumPlatneHlasy : public Kriterium<int, UzemnaJednotka>
{
private:
	const TypKola kolo_;
public:
	KriteriumPlatneHlasy(const TypKola kolo) : kolo_(kolo) {}

	int evaluate(const UzemnaJednotka& uzemnaJednotka) const override
	{
		return uzemnaJednotka.pocetPlatnychHlasov(kolo_);
	}
};

