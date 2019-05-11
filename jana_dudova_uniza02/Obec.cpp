#include "Obec.h"

bool Obec::patriDoVyssiehoCelku(const VyssiCelok& vyssiCelok) const
{
	return okres_->getKod() == vyssiCelok.getKod() || okres_->getKraj()->getKod() == vyssiCelok.getKod();
}

Okres* Obec::getOkres() const 
{ 
	return okres_; 
}


void Obec::setOkres(Okres* okres) 
{ 
	okres_ = okres; 
}

