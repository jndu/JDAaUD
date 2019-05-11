#pragma once

#include "VyssiCelok.h"

class Okres : public VyssiCelok
{
private:
	int kodKraja_;
	std::string nazovKraja_;

public:
	int getKodKraja() const;
	std::string getNazovKraja() const;

	void setKodKraja(int kodKraja);
	void setNazovKraja(const std::string& nazovKraja);
};