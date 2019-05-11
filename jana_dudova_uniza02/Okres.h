#pragma once

#include "VyssiCelok.h"
#include "Kraj.h"

class Okres : public VyssiCelok
{
private:
	Kraj* kraj_;

public:
	Kraj* getKraj() const;

	void setKraj(Kraj * kraj);
};