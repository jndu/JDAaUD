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
	structures::ArrayList<Obec*> obce_;
	structures::ArrayList<Okres*> okresy_;
	structures::ArrayList<Kraj*> kraje_;

	std::string odstranZnaky(const std::string& retazec, const std::function<bool(unsigned char)>& predikat);
	std::string odstranBieleZnaky(const std::string &str);
	std::string odstranUvodzovky(const std::string &str);
	int vyberCeleCislo(std::string retazec);
	double vyberDesatinneCislo(std::string retazec);
	std::string ocistiRetazec(const std::string& retazec);
	void nacitajObce();
	void nacitajHlasyZaKoloObec(const csv::Row& riadok, Kolo& kolo, const int spravnyKodObce);
	void nacitajKoloObec(const csv::Row& riadok, Kolo& kolo);
	Obec* nacitajObec(const csv::Row& riadok);
	void nacitajOkresy();
	void nacitajHlasyZaKoloOkres(const csv::Row& riadok, Kolo& kolo, const int spravnyKodOkresu);
	Okres* nacitajOkres(const csv::Row& riadok);
	void nacitajKoloOkres(const csv::Row& riadok, Kolo& kolo);
	void nacitajKraje();
	void nacitajHlasyZaKoloKraj(const csv::Row& riadok, Kolo& kolo, const int spravnyKodKraja);
	Kraj* nacitajKraj(const csv::Row& riadok);
	void nacitajKoloKraj(const csv::Row& riadok, Kolo& kolo);
	void nacitajKandidatov();
	void nacitajCislaKandidatovVDruhomKole();
	Kandidat* nacitajKandidata(const csv::Row& riadok);
	void nacitajData();

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
	void nacitaj();

	structures::ArrayList<Kandidat*> getKandidati() const { return kandidati_; }
	structures::ArrayList<Obec*> getObce() const { return obce_; }
	structures::ArrayList<Okres*> getOkresy() const { return okresy_; }
	structures::ArrayList<Kraj*> getKraje() const { return kraje_; }
};