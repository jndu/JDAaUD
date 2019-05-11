#include "VolebneUdaje.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

std::string VolebneUdaje::odstranZnaky(const std::string& retazec, const std::function<bool(unsigned char)>& predikat)
{
	if (retazec.empty())
	{
		return {};
	}

	std::string::size_type startIndex = 0U;
	while (startIndex < retazec.length() && predikat(static_cast<unsigned char>(retazec[startIndex])))
	{
		startIndex++;
	}

	std::string::size_type koniecIndex = retazec.length() - 1;
	while (koniecIndex > 0U && predikat(static_cast<unsigned char>(retazec[koniecIndex])))
	{
		koniecIndex--;
	}

	return startIndex <= koniecIndex ? retazec.substr(startIndex, koniecIndex - startIndex + 1) : std::string();
}

std::string VolebneUdaje::odstranBieleZnaky(const std::string &str)
{
	static const std::function<bool(unsigned char)> isSpaceWrapper = [](unsigned char c) { return static_cast<bool>(std::isspace(c)); };
	return odstranZnaky(str, isSpaceWrapper);
}

std::string VolebneUdaje::odstranUvodzovky(const std::string &str)
{
	static const std::function<bool(unsigned char)> isQuotes = [](unsigned char c) { return c == '\"'; };
	return odstranZnaky(str, isQuotes);
}

int VolebneUdaje::vyberCeleCislo(std::string retazec)
{
	retazec.erase(std::remove_if(retazec.begin(), retazec.end(), ::isspace), retazec.end());
	return std::stoi(retazec);
}

double VolebneUdaje::vyberDesatinneCislo(std::string retazec)
{
	retazec.erase(std::remove_if(retazec.begin(), retazec.end(), ::isspace), retazec.end());
	return std::stod(retazec);
}

std::string VolebneUdaje::ocistiRetazec(const std::string& retazec)
{
	return odstranBieleZnaky(odstranUvodzovky(odstranBieleZnaky(retazec)));
}

void VolebneUdaje::nacitajObce()
{
	csv::Parser file1 = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab02d_ANSI.csv");
	for (unsigned i = 0; i < file1.rowCount(); i++)
	{
		obce_.add(nacitajObec(file1.getRow(i)));
	}

	// doplnenie udajov pre druhe kolo
	csv::Parser file2 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab02d_ANSI.csv");
	for (unsigned i = 0; i < file2.rowCount(); i++)
	{
		nacitajKoloObec(file2.getRow(i), obce_[i]->getKolo2());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file3 = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab03e_ANSI.csv");
	for (unsigned i = 0; i < file3.rowCount(); i++)
	{
		Obec& obec = *obce_[i / pocetKandidatovVPrvomKole];
		nacitajHlasyZaKoloObec(file3.getRow(i), obec.getKolo1(), obec.getKod());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file4 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab03e_ANSI.csv");
	for (unsigned i = 0; i < file4.rowCount(); i++)
	{
		Obec& obec = *obce_[i / pocetKandidatovVDruhomKole];
		nacitajHlasyZaKoloObec(file4.getRow(i), obec.getKolo2(), obec.getKod());
	}
}

void VolebneUdaje::nacitajHlasyZaKoloObec(const csv::Row& riadok, Kolo& kolo, const int spravnyKodObce)
{
	int kandidat = vyberCeleCislo(riadok[8]);
	int pocetZiskanychHlasovZaKandidata = vyberCeleCislo(riadok[11]);
	kolo.setPocetZiskanychHlasovKandidat(kandidat, pocetZiskanychHlasovZaKandidata);
	int kodObce = vyberCeleCislo(riadok[6]);
	if (spravnyKodObce != kodObce)
	{
		throw std::exception("Obce nie su v suboroch usporiadane rovnako.");
	}
}

void VolebneUdaje::nacitajKoloObec(const csv::Row& riadok, Kolo& kolo)
{
	kolo.setPocetZapisanychVolicov(vyberCeleCislo(riadok[9]));
	kolo.setPocetVydanychObalok(vyberCeleCislo(riadok[10]));
	kolo.setUcastVolicovPercent(vyberDesatinneCislo(riadok[11]));
	kolo.setPocetOdovzdanychObalok(vyberCeleCislo(riadok[12]));
	kolo.setPodielOdovzdanychObalok(vyberDesatinneCislo(riadok[13]));
	kolo.setPocetPlatnychHlasovVsetkychKandidatov(vyberCeleCislo(riadok[14]));
	kolo.setPodielPlatnychHlasovVsetkychKandidatov(vyberDesatinneCislo(riadok[15]));
}

Obec* VolebneUdaje::nacitajObec(const csv::Row& riadok)
{
	Obec* obec = new Obec;
	obec->setTyp(TypUzemnejJednotky::OBEC);
	obec->setKodKraja(vyberCeleCislo(riadok[0]));
	obec->setNazovKraja(ocistiRetazec(riadok[1]));
	obec->setKodOkresu(vyberCeleCislo(riadok[4]));
	obec->setNazovOkresu(ocistiRetazec(riadok[5]));
	obec->setKod(vyberCeleCislo(riadok[6]));
	obec->setNazov(ocistiRetazec(riadok[7]));

	nacitajKoloObec(riadok, obec->getKolo1());

	return obec;
}

void VolebneUdaje::nacitajOkresy()
{
	csv::Parser file = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab02c_ANSI.csv");
	for (unsigned i = 0; i < file.rowCount(); i++)
	{
		okresy_.add(nacitajOkres(file.getRow(i)));
	}
	// doplnenie udajov pre druhe kolo
	csv::Parser file2 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab02c_ANSI.csv");
	for (unsigned i = 0; i < file2.rowCount(); i++)
	{
		nacitajKoloOkres(file2.getRow(i), okresy_[i]->getKolo2());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file3 = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab03d_ANSI.csv");
	for (unsigned i = 0; i < file3.rowCount(); i++)
	{
		Okres& okres = *okresy_[i / pocetKandidatovVPrvomKole];
		nacitajHlasyZaKoloOkres(file3.getRow(i), okres.getKolo1(), okres.getKod());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file4 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab03d_ANSI.csv");
	for (unsigned i = 0; i < file4.rowCount(); i++)
	{
		Okres& okres = *okresy_[i / pocetKandidatovVDruhomKole];
		nacitajHlasyZaKoloOkres(file4.getRow(i), okres.getKolo2(), okres.getKod());
	}
}

void VolebneUdaje::nacitajHlasyZaKoloOkres(const csv::Row& riadok, Kolo& kolo, const int spravnyKodOkresu)
{
	int kandidat = vyberCeleCislo(riadok[6]);
	int pocetZiskanychHlasovZaKandidata = vyberCeleCislo(riadok[9]);
	kolo.setPocetZiskanychHlasovKandidat(kandidat, pocetZiskanychHlasovZaKandidata);
	int kodOkresu = vyberCeleCislo(riadok[4]);
	if (spravnyKodOkresu != kodOkresu)
	{
		throw std::exception("Okresy nie su v suboroch usporiadane rovnako.");
	}
}

Okres* VolebneUdaje::nacitajOkres(const csv::Row& riadok)
{
	Okres* okres = new Okres;
	okres->setTyp(TypUzemnejJednotky::OKRES);
	okres->setKodKraja(vyberCeleCislo(riadok[0]));
	okres->setNazovKraja(ocistiRetazec(riadok[1]));
	okres->setKod(vyberCeleCislo(riadok[4]));
	okres->setNazov(ocistiRetazec(riadok[5]));

	nacitajKoloOkres(riadok, okres->getKolo1());

	return okres;
}

void VolebneUdaje::nacitajKoloOkres(const csv::Row& riadok, Kolo& kolo)
{
	kolo.setPocetZapisanychVolicov(vyberCeleCislo(riadok[7]));
	kolo.setPocetVydanychObalok(vyberCeleCislo(riadok[8]));
	kolo.setUcastVolicovPercent(vyberDesatinneCislo(riadok[9]));
	kolo.setPocetOdovzdanychObalok(vyberCeleCislo(riadok[10]));
	kolo.setPodielOdovzdanychObalok(vyberDesatinneCislo(riadok[11]));
	kolo.setPocetPlatnychHlasovVsetkychKandidatov(vyberCeleCislo(riadok[12]));
	kolo.setPodielPlatnychHlasovVsetkychKandidatov(vyberDesatinneCislo(riadok[13]));
}

void VolebneUdaje::nacitajKraje()
{
	csv::Parser file = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab02a_ANSI.csv");
	for (unsigned i = 0; i < file.rowCount(); i++)
	{
		kraje_.add(nacitajKraj(file.getRow(i)));
	}
	// doplnenie udajov pre druhe kolo
	csv::Parser file2 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab02a_ANSI.csv");
	for (unsigned i = 0; i < file2.rowCount(); i++)
	{
		nacitajKoloKraj(file2.getRow(i), kraje_[i]->getKolo2());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file3 = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab03b_ANSI.csv");
	for (unsigned i = 0; i < file3.rowCount(); i++)
	{
		Kraj& kraj = *kraje_[i / pocetKandidatovVPrvomKole];
		nacitajHlasyZaKoloKraj(file3.getRow(i), kraj.getKolo1(), kraj.getKod());
	}

	// doplnenie udajov o pocte hlasov pre kandidatov
	csv::Parser file4 = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab03b_ANSI.csv");
	for (unsigned i = 0; i < file4.rowCount(); i++)
	{
		Kraj& kraj = *kraje_[i / pocetKandidatovVDruhomKole];
		nacitajHlasyZaKoloKraj(file4.getRow(i), kraj.getKolo2(), kraj.getKod());
	}
}

void VolebneUdaje::nacitajHlasyZaKoloKraj(const csv::Row& riadok, Kolo& kolo, const int spravnyKodKraja)
{
	int kandidat = vyberCeleCislo(riadok[2]);
	int pocetZiskanychHlasovZaKandidata = vyberCeleCislo(riadok[5]);
	kolo.setPocetZiskanychHlasovKandidat(kandidat, pocetZiskanychHlasovZaKandidata);
	int kodKraja = vyberCeleCislo(riadok[0]);
	if (spravnyKodKraja != kodKraja)
	{
		throw std::exception("Kraje nie su v suboroch usporiadane rovnako.");
	}
}

Kraj* VolebneUdaje::nacitajKraj(const csv::Row& riadok)
{
	Kraj* kraj = new Kraj;
	kraj->setTyp(TypUzemnejJednotky::KRAJ);
	kraj->setKod(vyberCeleCislo(riadok[0]));
	kraj->setNazov(ocistiRetazec(riadok[1]));

	nacitajKoloKraj(riadok, kraj->getKolo1());

	return kraj;
}

void VolebneUdaje::nacitajKoloKraj(const csv::Row& riadok, Kolo& kolo)
{
	kolo.setPocetZapisanychVolicov(vyberCeleCislo(riadok[3]));
	kolo.setPocetVydanychObalok(vyberCeleCislo(riadok[4]));
	kolo.setUcastVolicovPercent(vyberDesatinneCislo(riadok[5]));
	kolo.setPocetOdovzdanychObalok(vyberCeleCislo(riadok[6]));
	kolo.setPodielOdovzdanychObalok(vyberDesatinneCislo(riadok[7]));
	kolo.setPocetPlatnychHlasovVsetkychKandidatov(vyberCeleCislo(riadok[8]));
	kolo.setPodielPlatnychHlasovVsetkychKandidatov(vyberDesatinneCislo(riadok[9]));
}

void VolebneUdaje::nacitajKandidatov()
{
	csv::Parser file = csv::Parser("csvANSI/kolo1/PRE_2019_KOLO1_tab0a_ANSI.csv");
	pocetKandidatovVPrvomKole = file.rowCount();
	for (unsigned i = 0; i < file.rowCount(); i++)
	{
		kandidati_.add(nacitajKandidata(file.getRow(i)));
	}

	nacitajCislaKandidatovVDruhomKole();
}

void VolebneUdaje::nacitajCislaKandidatovVDruhomKole()
{
	csv::Parser file = csv::Parser("csvANSI/kolo2/PRE_2019_KOLO2_tab0a_ANSI.csv");
	pocetKandidatovVDruhomKole = file.rowCount();

	for (unsigned i = 0; i < file.rowCount(); i++)
	{
		const csv::Row riadok = file.getRow(i);
		std::string meno = ocistiRetazec(riadok[1]);
		std::string priezvisko = ocistiRetazec(riadok[2]);
		for (unsigned j = 0; j < kandidati_.size(); j++)
		{
			Kandidat& kandidat = *kandidati_[j];
			if (kandidat.getMeno() == meno && kandidat.getPiezvisko() == priezvisko)
			{
				int poradoveCislo = vyberCeleCislo(riadok[0]);
				kandidat.setPoradoveCislo2(poradoveCislo);
				break;
			}
		}
	}
}

Kandidat* VolebneUdaje::nacitajKandidata(const csv::Row& riadok)
{
	Kandidat* kandidat = new Kandidat;
	kandidat->setPoradoveCislo1(vyberCeleCislo(riadok[0]));
	kandidat->setMeno(ocistiRetazec(riadok[1]));
	kandidat->setPriezvisko(ocistiRetazec(riadok[2]));

	return kandidat;
}

void VolebneUdaje::nacitajData()
{
	nacitajKandidatov();
	nacitajObce();
	nacitajOkresy();
	nacitajKraje();
}

void VolebneUdaje::uvolniData()
{
	uvolniArrayList(obce_);
	uvolniArrayList(okresy_);
	uvolniArrayList(kraje_);
	uvolniArrayList(kandidati_);
}

VolebneUdaje::~VolebneUdaje()
{
	uvolniData();
}

void VolebneUdaje::nacitaj()
{
	nacitajData();
}