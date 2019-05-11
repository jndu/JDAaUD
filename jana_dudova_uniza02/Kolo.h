#pragma once

#include "structures/table/sorted_sequence_table.h"

enum class TypKola { PRVE, DRUHE, OBE };

class Kolo
{
private:
	structures::SortedSequenceTable<int, int> pocetZiskanychHlasovKandidat_;
	int pocetZapisanychVolicov_;
	int pocetVydanychObalok_;
	double ucastVolicovPercent_;
	int pocetOdovzdanychObalok_;
	double podielOdovzdanychObalok_;
	int pocetPlatnychHlasovVsetkychKandidatov_;
	double podielPlatnychHlasovVsetkychKandidatov_;

public:
	int getPocetZiskanychHlasovKandidat(int poradoveCislo) const;
	int getPocetZapisanychVolicov() const;
	int getPocetVydanychObalok() const;
	double getUcastVolicovPercent() const;
	int getPocetOdovzdanychObalok() const;
	double getPodielOdovzdanychObalok() const;
	int getPocetPlatnychHlasovVsetkychKandidatov() const;
	double getPodielPlatnychHlasovVsetkychKandidatov() const;

	void setPocetZiskanychHlasovKandidat(int poradoveCislo, int pocetZiskanychHlasov);
	void setPocetZapisanychVolicov(int pocetZapisanychVolicov);
	void setPocetVydanychObalok(int pocetVydanychObalok);
	void setUcastVolicovPercent(double ucastVolicovPercent);
	void setPocetOdovzdanychObalok(int pocetOdovzdanychObalok);
	void setPodielOdovzdanychObalok(double podielOdovzdanychObalok);
	void setPocetPlatnychHlasovVsetkychKandidatov(int pocetPlatnychHlasovVsetkychKandidatov);
	void setPodielPlatnychHlasovVsetkychKandidatov(double podielPlatnychHlasovVsetkychKandidatov);
};