#pragma once

#include <functional>

#include "CSVparser.hpp"

#include "Kandidat.h"
#include "Kraj.h"
#include "Okres.h"
#include "Obec.h"

class VolebneUdaje
{
private:
	int pocetKandidatovVPrvomKole = 0;
	int pocetKandidatovVDruhomKole = 0;

	structures::ArrayList<Kandidat*> kandidati_;
	structures::ArrayList<Obec*> obce_ = structures::ArrayList<Obec*>(3000); // ocakavany pocet obci 3000
	structures::ArrayList<Okres*> okresy_ = structures::ArrayList<Okres*>(80); // ocakavany pocet okresov 80
	structures::ArrayList<Kraj*> kraje_ = structures::ArrayList<Kraj*>(10); // ocakavany pocet krajov 10

	std::string odstranZnaky(const std::string& retazec, const std::function<bool(unsigned char)>& predikat);
	std::string odstranBieleZnaky(const std::string &str);
	std::string odstranUvodzovky(const std::string &str);
	int vyberCeleCislo(std::string retazec);
	double vyberDesatinneCislo(std::string retazec);
	std::string ocistiRetazec(const std::string& retazec);
	void nacitajHlasyZaKoloObec(const csv::Row& riadok, Kolo& kolo, const int spravnyKodObce);
	void nacitajKoloObec(const csv::Row& riadok, Kolo& kolo);
	Obec* nacitajObec(const csv::Row& riadok, structures::SortedSequenceTable<int, Okres*> okresy);
	void nacitajHlasyZaKoloOkres(const csv::Row& riadok, Kolo& kolo, const int spravnyKodOkresu);
	Okres* nacitajOkres(const csv::Row& riadok, structures::SortedSequenceTable<int, Kraj*> kraje);
	void nacitajKoloOkres(const csv::Row& riadok, Kolo& kolo);
	void nacitajHlasyZaKoloKraj(const csv::Row& riadok, Kolo& kolo, const int spravnyKodKraja);
	Kraj* nacitajKraj(const csv::Row& riadok);
	void nacitajKoloKraj(const csv::Row& riadok, Kolo& kolo);
	void nacitajCislaKandidatovVDruhomKole();
	Kandidat* nacitajKandidata(const csv::Row& riadok);

	template<typename T>
	void uvolniArrayList(structures::ArrayList<T*>& arrayList)
	{
		for (T* item : arrayList)
		{
			delete item;
		}
	}

	void uvolniData();

public:
	~VolebneUdaje();

	void nacitajObce(structures::SortedSequenceTable<int, Okres*> okresy);
	void nacitajOkresy(structures::SortedSequenceTable<int, Kraj*> kraje);
	void nacitajKraje();
	void nacitajKandidatov();

	structures::ArrayList<Kandidat*> getKandidati() const { return kandidati_; }
	structures::ArrayList<Obec*> getObce() const { return obce_; }
	structures::ArrayList<Okres*> getOkresy() const { return okresy_; }
	structures::ArrayList<Kraj*> getKraje() const { return kraje_; }
};