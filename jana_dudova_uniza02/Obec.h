#pragma once

#include "UzemnaJednotka.h"
#include "VyssiCelok.h"

class Obec : public UzemnaJednotka
{
private:
	int kodKraja_;
	std::string nazovKraja_;
	int kodOkresu_;
	std::string nazovOkresu_;

public:
	bool patriDoVyssiehoCelku(const VyssiCelok& vyssiCelok) const;

	int getKodKraja() const;
	std::string getNazovKraja() const;
	int getKodOkresu() const;
	std::string getNazovOkresu() const;

	void setKodKraja(int kodKraja);
	void setNazovKraja(const std::string& nazovKraja);
	void setKodOkresu(int kodOkresu);
	void setNazovOkresu(const std::string& nazovOkresu);
};