#pragma once

#include "UzemnaJednotka.h"
#include "VyssiCelok.h"
#include "Okres.h"

class Obec : public UzemnaJednotka
{
private:
	Okres* okres_;

public:
	bool patriDoVyssiehoCelku(const VyssiCelok& vyssiCelok) const;

	Okres* getOkres() const;
	void setOkres(Okres* okres);
};