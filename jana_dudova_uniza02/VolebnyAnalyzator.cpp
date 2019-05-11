#include "VolebnyAnalyzator.h"

void VolebnyAnalyzator::zobrazMenu()
{
	std::cout << "0 - koniec" << std::endl;
	std::cout << "1 - VypÌsanie inform·ciÌ o obciach" << std::endl;
	std::cout << "2 - Zoradenie obcÌ" << std::endl;
	std::cout << "3 - VypÌsanie inform·ciÌ o ˙zemn˝ch jednotk·ch" << std::endl;
	std::cout << "4 - Zoradenie ˙zemn˝ch jednotiek spÂÚaj˙cich dan˝ filter" << std::endl;
	std::cout << "5 - VypÌsanie v˝sledkov kandid·ta v ˙zemnej jednotke" << std::endl;
	std::cout << "6 - Zoradenie kandid·tov podæa v˝sledkov v ˙zemn˝ch jednotk·ch" << std::endl;
	std::cout << "7 - VypÌsane v˝berov˝ch kritÈriÌ" << std::endl;
}

std::string VolebnyAnalyzator::ziskajVolbu()
{
	std::string volba;
	std::cout << "Zadaj voæbu: ";
	getline(std::cin, volba);
	return volba;
}

bool VolebnyAnalyzator::vykonajVolbu(const std::string& volba)
{
	if (volba == "0") return false;
	else if (volba == "1") vypisInformacieOObciach();
	else if (volba == "2") zoradenieObci();
	else if (volba == "3") vypisanieInformaciiOUzemnychJednotkach();
	else if (volba == "4") zoradenieUzemnychJednotiekSplnajucichDanyFilter();
	else if (volba == "5") vypisanieVysledkovKandidataVUzemnejJednotke();
	else if (volba == "6") zoradenieKandidatovPodlaVysledkovVUzemnychJednotkach();
	else if (volba == "7") vypisanieVyberovychKriterii();
	else
	{
		std::cout << "Nezn·ma voæba!" << std::endl;
	}
	return true;
}

// hladanie v kolekciach

const VyssiCelok* VolebnyAnalyzator::najdiVyssiCelokPodlaKodu(const int kod)
{
	if (usporiadaneOkresy_.containsKey(kod))
	{
		return usporiadaneOkresy_[kod];
	}
	else if (usporiadaneKraje_.containsKey(kod))
	{
		return usporiadaneKraje_[kod];
	}

	return nullptr;
}

const UzemnaJednotka* VolebnyAnalyzator::najdiUzemnuJednotkuPodlaKodu(const int kod)
{
	if (usporiadaneObce_.containsKey(kod))
	{
		return usporiadaneObce_[kod];
	}

	return najdiVyssiCelokPodlaKodu(kod);
}

const Kandidat* VolebnyAnalyzator::najdiKandidataPodlaMena(const std::string& menoAPriezvisko)
{
	return usporiadaniKandidati_[menoAPriezvisko];
}

// vyber objektov uzivatelom

const VyssiCelok* VolebnyAnalyzator::vyberVyssiCelok()
{
	static const std::function<bool(int)> podmienka = [this](int kod)
	{
		return usporiadaneOkresy_.containsKey(kod) || usporiadaneKraje_.containsKey(kod);
	};
	int kod = vstup.ziskajVstupSPodmienkou(podmienka, "Zadaj kÛd kraja alebo okresu: ");
	return najdiVyssiCelokPodlaKodu(kod);
}

const Kandidat* VolebnyAnalyzator::vyberKandidata()
{
	static const std::function<bool(std::string)> podmienka = [this](const std::string& meno)
	{
		return usporiadaniKandidati_.containsKey(meno);
	};
	std::string menoAPriezvisko = vstup.ziskajVstupSPodmienkou(podmienka, "Zadaj meno kandid·ta vo form·te Meno Priezvisko: ");
	return najdiKandidataPodlaMena(menoAPriezvisko);
}

const UzemnaJednotka* VolebnyAnalyzator::vyberUzemnuJednotku()
{
	static const std::function<bool(int)> podmienka = [this](int kod)
	{
		return usporiadaneObce_.containsKey(kod) || usporiadaneOkresy_.containsKey(kod) || usporiadaneKraje_.containsKey(kod);
	};
	int kod = vstup.ziskajVstupSPodmienkou(podmienka, "Zadaj kÛd kraja, okresu alebo obce: ");
	return najdiUzemnuJednotkuPodlaKodu(kod);
}

TypKola VolebnyAnalyzator::vyberLenJednoKolo()
{
	static const std::function<bool(int)> podmienka = [](int cislo) { return cislo >= 1 && cislo <= 2; };
	int cisloKola = vstup.ziskajVstupSPodmienkou(podmienka, "Zadaj ËÌslo kola (1 alebo 2): ");

	if (cisloKola == 1) return TypKola::PRVE;
	else return TypKola::DRUHE;
}

TypKola VolebnyAnalyzator::vyberKolo()
{
	static const std::function<bool(int)> podmienka = [](int cislo) { return cislo >= 0 && cislo <= 2; };
	int cisloKola = vstup.ziskajVstupSPodmienkou(podmienka, "Zadaj ËÌslo kola (1 alebo 2) alebo 0 pre obe kol·: ");

	if (cisloKola == 1) return TypKola::PRVE;
	else if (cisloKola == 2) return TypKola::DRUHE;
	else return TypKola::OBE;
}

// tvorba kriterii

KriteriumPrislusnostObce VolebnyAnalyzator::vytvorKriteriumPrislusnostObce()
{
	std::cout << "Parametere pre kritÈrium prÌsluönosù obce:" << std::endl;
	const VyssiCelok* vyssiCelok = vyberVyssiCelok();
	return KriteriumPrislusnostObce(*vyssiCelok);
}

KriteriumVolici VolebnyAnalyzator::vytvorKriteriumVolici()
{
	std::cout << "Parametere pre kritÈrium voliËi:" << std::endl;
	TypKola kolo = vyberLenJednoKolo();
	return KriteriumVolici(kolo);
}

KriteriumVydaneObalky VolebnyAnalyzator::vytvorKriteriumVydaneObalky()
{
	std::cout << "Parametere pre kritÈrium vydanÈ ob·lky:" << std::endl;
	TypKola kolo = vyberKolo();
	return KriteriumVydaneObalky(kolo);
}

KriteriumUcast VolebnyAnalyzator::vytvorKriteriumUcast()
{
	std::cout << "Parametere pre kritÈrium ˙Ëasù:" << std::endl;
	TypKola kolo = vyberLenJednoKolo();
	return KriteriumUcast(kolo);
}

KriteriumOdovzdaneObalky VolebnyAnalyzator::vytvorKriteriumOdovzdaneObalky()
{
	std::cout << "Parametere pre kritÈrium odovzdanÈ ob·lky:" << std::endl;
	TypKola kolo = vyberKolo();
	return KriteriumOdovzdaneObalky(kolo);
}

KriteriumHlasyOdovzdane VolebnyAnalyzator::vytvorKriteriumHlasyOdovzdane()
{
	std::cout << "Parametere pre kritÈrium hlasy odovzdanÈ:" << std::endl;
	TypKola kolo = vyberKolo();
	const Kandidat* kandidat = vyberKandidata();
	return KriteriumHlasyOdovzdane(*kandidat, kolo);
}

KriteriumHlasyZiskane VolebnyAnalyzator::vytvorKriteriumHlasyZiskane()
{
	std::cout << "Parametere pre kritÈrium hlasy zÌskanÈ" << std::endl;
	TypKola kolo = vyberKolo();
	const UzemnaJednotka* uzemnaJednotka = vyberUzemnuJednotku();
	return KriteriumHlasyZiskane(*uzemnaJednotka, kolo);
}

KriteriumPlatneHlasy VolebnyAnalyzator::vytvorKriteriumPlatneHlasy()
{
	std::cout << "Parametere pre kritÈrium platnÈ hlasy:" << std::endl;
	TypKola kolo = vyberKolo();
	return KriteriumPlatneHlasy(kolo);
}

// tvorba filtrov

FilterNazov VolebnyAnalyzator::vytvorFilterNazov(const KriteriumNazov& kriteriumNazov)
{
	std::cout << "Budovanie filtra n·zov" << std::endl;
	std::string nazov = vstup.ziskajRetazec("Zadaj parameter n·zov: ");
	return FilterNazov(kriteriumNazov, nazov);
}

FilterVolici VolebnyAnalyzator::vytvorFilterVolici(const KriteriumVolici& kriteriumVolici)
{
	std::cout << "Budovanie filtra voliËi" << std::endl;
	int minimalneVolicov = vstup.ziskajNezaporneCeleCislo("Zadaj minim·lny poËet voliËov: ");
	int maximalneVolicov = vstup.ziskajNezaporneCeleCislo("Zadaj maxim·lny poËet voliËov: ");
	if (minimalneVolicov > maximalneVolicov)
	{
		std::swap(minimalneVolicov, maximalneVolicov);
	}
	return FilterVolici(kriteriumVolici, minimalneVolicov, maximalneVolicov);
}

FilterUcast VolebnyAnalyzator::vytvorFilterUcast(const KriteriumUcast& kriteriumUcast)
{
	std::cout << "Budovanie filtra ˙Ëasù" << std::endl;
	double minimalnaUcast = vstup.ziskajPercent("Zadaj minim·lnu ˙Ëasù v percent·ch (bez %): ");
	double maximalnaUcast = vstup.ziskajPercent("Zadaj maxim·lnu ˙Ëasù v percent·ch (bez %): ");
	if (minimalnaUcast > maximalnaUcast)
	{
		std::swap(minimalnaUcast, maximalnaUcast);
	}
	return FilterUcast(kriteriumUcast, minimalnaUcast, maximalnaUcast);
}

FilterMeno VolebnyAnalyzator::vytvorFilterMeno(const KriteriumMeno& kriteriumMeno)
{
	std::cout << "Budovanie filtra meno" << std::endl;
	std::string meno = vstup.ziskajRetazec("Zadaj parameter meno: ");
	return FilterMeno(kriteriumMeno, meno);
}

// akcie z menu

void VolebnyAnalyzator::vypisInformacieOObciach()
{
	structures::ArrayList<Obec*> result;

	std::cout << "a - F_N·zov\nb - F_VoliËi\nc - F_⁄Ëasù" << std::endl;
	std::string volba = ziskajVolbu();
	if (volba == "a")
	{
		KriteriumNazov kriteriumNazov;
		auto filter = vytvorFilterNazov(kriteriumNazov);
		result = pouziFilter(obce_, filter);
	}
	else if (volba == "b")
	{
		auto kriteriumVolici = vytvorKriteriumVolici();
		auto filter = vytvorFilterVolici(kriteriumVolici);
		result = pouziFilter(obce_, filter);
	}
	else if (volba == "c")
	{
		auto kriteriumUcast = vytvorKriteriumUcast();
		auto filter = vytvorFilterUcast(kriteriumUcast);
		result = pouziFilter(obce_, filter);
	}
	else
	{
		std::cout << "Nezn·ma voæba!" << std::endl;
		return;
	}

	KriteriumNazov kNazov;
	KriteriumVolici kVolici(TypKola::OBE);
	KriteriumVydaneObalky kVydaneObalky(TypKola::OBE);
	KriteriumUcast kUcast(TypKola::OBE);
	KriteriumOdovzdaneObalky kOdovzdaneObalky(TypKola::OBE);
	KriteriumPlatneHlasy kPlatneHlasy(TypKola::OBE);

	// namiesto hladanie okresu a kraja sa dali pouzit nazvy priamo z item lebo je to obec a obsahuje ich
	for (const auto obec : result)
	{
		std::cout << kNazov.evaluate(*obec) << "; " <<
			obec->getOkres()->getNazov() /*kNazov.evaluate(*usporiadaneOkresy_[obec->getKodOkresu()])*/ << "; " <<
			obec->getOkres()->getKraj()->getNazov() /* kNazov.evaluate(*usporiadaneKraje_[obec->getKodKraja()]) */ << "; " <<
			kVolici.evaluate(*obec) << "; " <<
			kVydaneObalky.evaluate(*obec) << "; " <<
			kUcast.evaluate(*obec) << "; " <<
			kOdovzdaneObalky.evaluate(*obec) << "; " <<
			kPlatneHlasy.evaluate(*obec) << std::endl;
	}
}

void VolebnyAnalyzator::zoradenieObci()
{
	std::cout << "a - K_N·zov\nb - K_VoliËi\nc - K_⁄Ëasù" << std::endl;
	std::string volba = ziskajVolbu();
	if (volba == "a")
	{
		KriteriumNazov kriteriumNazov;
		zoradAVypisObcePodlaKriteria(obce_, kriteriumNazov);
	}
	else if (volba == "b")
	{
		auto kriteriumVolici = vytvorKriteriumVolici();
		zoradAVypisObcePodlaKriteria(obce_, kriteriumVolici);
	}
	else if (volba == "c")
	{
		auto kriteriumUcast = vytvorKriteriumUcast();
		zoradAVypisObcePodlaKriteria(obce_, kriteriumUcast);
	}
	else
	{
		std::cout << "Nezn·ma voæba!" << std::endl;
		return;
	}
}

void VolebnyAnalyzator::vypisanieInformaciiOUzemnychJednotkach()
{
	structures::ArrayList<UzemnaJednotka*> result;

	std::cout << "a - F_N·zov\nb - F_VoliËi\nc - F_⁄Ëasù" << std::endl;
	std::string volba = ziskajVolbu();
	if (volba == "a")
	{
		KriteriumNazov kriteriumNazov;
		auto filter = vytvorFilterNazov(kriteriumNazov);
		result = pouziFilter(uzemneJednotky_, filter);
	}
	else if (volba == "b")
	{
		auto kriteriumVolici = vytvorKriteriumVolici();
		auto filter = vytvorFilterVolici(kriteriumVolici);
		result = pouziFilter(uzemneJednotky_, filter);
	}
	else if (volba == "c")
	{
		auto kriteriumUcast = vytvorKriteriumUcast();
		auto filter = vytvorFilterUcast(kriteriumUcast);
		result = pouziFilter(uzemneJednotky_, filter);
	}
	else
	{
		std::cout << "Nezn·ma voæba!" << std::endl;
		return;
	}

	KriteriumNazov kNazov;
	KriteriumVolici kVolici(TypKola::OBE);
	KriteriumVydaneObalky kVydaneObalky(TypKola::OBE);
	KriteriumUcast kUcast(TypKola::OBE);
	KriteriumOdovzdaneObalky kOdovzdaneObalky(TypKola::OBE);
	KriteriumPlatneHlasy kPlatneHlasy(TypKola::OBE);

	for (const auto item : result)
	{
		std::cout << kNazov.evaluate(*item) << "; ";
		if (item->getTyp() == TypUzemnejJednotky::OBEC)
		{
			Obec * obec = dynamic_cast<Obec*>(item);
			// namiesto hladania by stacilo pristupit k clenom objektu obec lebo obsahuje nazov kraja aj okresu
			std::cout << obec->getOkres()->getNazov() /* kNazov.evaluate(*usporiadaneOkresy_[obec->getKodOkresu()]) */ << "; " <<
				obec->getOkres()->getKraj()->getNazov() /* kNazov.evaluate(*usporiadaneKraje_[obec->getKodKraja()]) */ << "; ";
		}
		else if (item->getTyp() == TypUzemnejJednotky::OKRES)
		{
			//Okres * okres = dynamic_cast<Okres*>(item);
			std::cout << dynamic_cast<Okres*>(item)->getKraj()->getNazov() /*kNazov.evaluate(*usporiadaneKraje_[okres->getKodKraja()])*/ << "; ";
		}
		std::cout << kVolici.evaluate(*item) << "; " <<
			kVydaneObalky.evaluate(*item) << "; " <<
			kUcast.evaluate(*item) << "; " <<
			kOdovzdaneObalky.evaluate(*item) << "; " <<
			kPlatneHlasy.evaluate(*item) << std::endl;
	}
}

void VolebnyAnalyzator::zoradenieUzemnychJednotiekSplnajucichDanyFilter()
{
	std::cout << "a - K_N·zov\nb - K_VoliËi\nc - K_⁄Ëasù" << std::endl;
	std::string volba = ziskajVolbu();

	KriteriumPrislusnostObce kPrislusnostObce = vytvorKriteriumPrislusnostObce();
	FilterPrislusnostObce fPrislusnostObce(kPrislusnostObce);
	auto vysledok1 = pouziFilter(obce_, fPrislusnostObce);

	KriteriumUcast kUcast = vytvorKriteriumUcast();
	FilterUcast fUcast = vytvorFilterUcast(kUcast);
	auto vysledok2 = pouziFilter(vysledok1, fUcast);

	if (volba == "a")
	{
		KriteriumNazov kriteriumNazov;
		zoradAVypisObcePodlaKriteria(vysledok2, kriteriumNazov);
	}
	else if (volba == "b")
	{
		auto kriteriumVolici = vytvorKriteriumVolici();
		zoradAVypisObcePodlaKriteria(vysledok2, kriteriumVolici);
	}
	else if (volba == "c")
	{
		auto kriteriumUcast = vytvorKriteriumUcast();
		zoradAVypisObcePodlaKriteria(vysledok2, kriteriumUcast);
	}
	else
	{
		std::cout << "Nezn·ma voæba!" << std::endl;
		return;
	}
}

void VolebnyAnalyzator::vypisanieVysledkovKandidataVUzemnejJednotke()
{
	KriteriumMeno kMeno;
	FilterMeno fMeno = vytvorFilterMeno(kMeno);
	auto kandidati = pouziFilter(kandidati_, fMeno);

	KriteriumNazov kNazov;
	FilterNazov fNazov = vytvorFilterNazov(kNazov);
	auto vysledok = pouziFilter(uzemneJednotky_, fNazov);

	KriteriumVolici kVolici = vytvorKriteriumVolici();
	FilterVolici fVolici = vytvorFilterVolici(kVolici);
	vysledok = pouziFilter(vysledok, fVolici);

	KriteriumUcast kUcast = vytvorKriteriumUcast();
	FilterUcast fUcast = vytvorFilterUcast(kUcast);
	vysledok = pouziFilter(vysledok, fUcast);

	KriteriumVydaneObalky kVydaneObalky = vytvorKriteriumVydaneObalky();

	std::cout << "Parameter kolo pre kritÈrium hlasy odovzdanÈ: ";
	TypKola hlasyOdovzdaneKolo = vyberKolo();

	for (const auto kandidat : kandidati)
	{
		KriteriumHlasyOdovzdane kHlasyOdovzdane(*kandidat, hlasyOdovzdaneKolo);
		for (const auto uzemnaJednotka : vysledok)
		{
			std::cout << kandidat->getCeleMeno() << "; " <<
				kNazov.evaluate(*uzemnaJednotka) << "; " <<
				kVolici.evaluate(*uzemnaJednotka) << "; " <<
				kVydaneObalky.evaluate(*uzemnaJednotka) << "; " <<
				kHlasyOdovzdane.evaluate(*uzemnaJednotka) << std::endl;
		}
	}
}

void VolebnyAnalyzator::zoradenieKandidatovPodlaVysledkovVUzemnychJednotkach()
{
	KriteriumMeno kMeno;
	FilterMeno fMeno = vytvorFilterMeno(kMeno);
	auto kandidati = pouziFilter(kandidati_, fMeno);

	KriteriumNazov kNazov;
	FilterNazov fNazov = vytvorFilterNazov(kNazov);
	auto vysledok = pouziFilter(uzemneJednotky_, fNazov);

	KriteriumVolici kVolici = vytvorKriteriumVolici();
	FilterVolici fVolici = vytvorFilterVolici(kVolici);
	vysledok = pouziFilter(vysledok, fVolici);

	KriteriumUcast kUcast = vytvorKriteriumUcast();
	FilterUcast fUcast = vytvorFilterUcast(kUcast);
	vysledok = pouziFilter(vysledok, fUcast);

	// napocitanie hlasov
	TypKola kolo = vyberKolo();
	structures::SortedSequenceTable<std::string, int> sumarneHlasyZiskane;
	for (const auto kandidat : kandidati)
	{
		for (const auto uzemnaJednotka : vysledok)
		{
			KriteriumHlasyZiskane kHlasyZiskane(*uzemnaJednotka, kolo);
			int ziskaneHlasy = kHlasyZiskane.evaluate(*kandidat);
			if (sumarneHlasyZiskane.containsKey(kandidat->getCeleMeno()))
			{
				sumarneHlasyZiskane[kandidat->getCeleMeno()] += ziskaneHlasy;
			}
			else
			{
				sumarneHlasyZiskane.insert(kandidat->getCeleMeno(), ziskaneHlasy);
			}
		}
	}

	// do listu aby sa dal Ìsù odzadu, lebo SortedSequenceTable nedovolÌ reverse ani nem· rbegin rend
	structures::ArrayList<MyPair<int, std::string>*> kandidatiList;
	for (const auto& sumarneHlasyPrvok : sumarneHlasyZiskane)
	{
		auto pair = new MyPair<int, std::string>();
		pair->first = sumarneHlasyPrvok->accessData();
		pair->second = sumarneHlasyPrvok->getKey();
		kandidatiList.add(pair);
	}

	// usporiadanie a vypis
	zoradVzostupne(kandidatiList);
	std::cout << "Vzostupne: " << std::endl;
	for (const auto kandidatVysledok : kandidatiList)
	{
		const Kandidat* kandidat = usporiadaniKandidati_[kandidatVysledok->second];
		for (const auto uzemnaJednotka : vysledok)
		{
			KriteriumHlasyZiskane kHlasyZiskane(*uzemnaJednotka, kolo);
			std::cout << kMeno.evaluate(*kandidat) << "; " <<
				kHlasyZiskane.evaluate(*kandidat) << "; " <<
				kNazov.evaluate(*uzemnaJednotka) << std::endl;
		}
	}

	zoradZostupne(kandidatiList);
	std::cout << "Zostupne: " << std::endl;
	for (const auto kandidatVysledok : kandidatiList)
	{
		const Kandidat* kandidat = usporiadaniKandidati_[kandidatVysledok->second];
		for (const auto uzemnaJednotka : vysledok)
		{
			KriteriumHlasyZiskane kHlasyZiskane(*uzemnaJednotka, kolo);
			std::cout << kMeno.evaluate(*kandidat) << "; " <<
				kHlasyZiskane.evaluate(*kandidat) << "; " <<
				kNazov.evaluate(*uzemnaJednotka) << std::endl;
		}
	}

	uvolniArrayList(kandidatiList);
}

void VolebnyAnalyzator::vypisanieVyberovychKriterii()
{
	KriteriumNazov kNazov;
	FilterNazov fNazov = vytvorFilterNazov(kNazov);
	auto vysledok = pouziFilter(uzemneJednotky_, fNazov);

	KriteriumVolici kVolici = vytvorKriteriumVolici();
	FilterVolici fVolici = vytvorFilterVolici(kVolici);
	vysledok = pouziFilter(vysledok, fVolici);

	KriteriumUcast kUcast = vytvorKriteriumUcast();
	FilterUcast fUcast = vytvorFilterUcast(kUcast);
	vysledok = pouziFilter(vysledok, fUcast);

	const Kandidat* kandidat = vyberKandidata();

	std::cout << "Kolo pre v˝berovÈ kritÈrium najviac hlasov" << std::endl;
	TypKola kolo1 = vyberKolo();
	std::cout << "Kolo pre v˝berovÈ kritÈrium najmenej hlasov" << std::endl;
	TypKola kolo2 = vyberKolo();
	std::cout << "Kolo pre v˝berovÈ kritÈrium nastabilnejöie v˝sledky, pre kritÈrium 1" << std::endl;
	TypKola kolo3 = vyberKolo();
	std::cout << "Kolo pre v˝berovÈ kritÈrium nastabilnejöie v˝sledky, pre kritÈrium 2" << std::endl;
	TypKola kolo4 = vyberKolo();

	VyberoveKriteriumNajviacHlasov vbNajviacHlasov(*kandidat, kolo1);
	VyberoveKriteriumNajmenejHlasov vbNajmenejHlasov(*kandidat, kolo2);
	VyberoveKriteriumNajstabilnejsieVysledky vbNajstabilnejsieVysledky(*kandidat, kolo3, *kandidat, kolo4);

	auto najviacHlasovUzemnaJednotka = vbNajviacHlasov.evaluate(vysledok);
	auto najmenejHlasovUzemnaJednotka = vbNajmenejHlasov.evaluate(vysledok);
	auto najstabilnejsieVysledkyUzemnaJednotka = vbNajstabilnejsieVysledky.evaluate(vysledok);

	std::cout << kandidat->getCeleMeno() << std::endl;

	KriteriumHlasyZiskane kHlasyZiskaneNajviac(*najviacHlasovUzemnaJednotka, kolo1);
	std::cout << "V˝berovÈ kritÈrium najviac hlasov" << std::endl;
	std::cout << kHlasyZiskaneNajviac.evaluate(*kandidat) << "; " << kNazov.evaluate(*najviacHlasovUzemnaJednotka) << std::endl;

	KriteriumHlasyZiskane kHlasyZiskaneNajmenej(*najmenejHlasovUzemnaJednotka, kolo2);
	std::cout << "V˝berovÈ kritÈrium najmenej hlasov" << std::endl;
	std::cout << kHlasyZiskaneNajmenej.evaluate(*kandidat) << "; " << kNazov.evaluate(*najmenejHlasovUzemnaJednotka) << std::endl;

	KriteriumHlasyZiskane kHlasyZiskaneNajstabilnejsieKolo3(*najstabilnejsieVysledkyUzemnaJednotka, kolo3);
	KriteriumHlasyZiskane kHlasyZiskaneNajstabilnejsieKolo4(*najstabilnejsieVysledkyUzemnaJednotka, kolo4);
	std::cout << "V˝berovÈ kritÈrium najstabilnejöie v˝sledky" << std::endl;
	std::cout << "Za kolo kritÈria 1 : " << kHlasyZiskaneNajstabilnejsieKolo3.evaluate(*kandidat) << "; " <<
		"Za kolo kritÈria 2 : " << kHlasyZiskaneNajstabilnejsieKolo4.evaluate(*kandidat) << "; " <<
		kNazov.evaluate(*najstabilnejsieVysledkyUzemnaJednotka) << std::endl;
}

void VolebnyAnalyzator::spusti()
{
	using namespace std;

	//std::locale::global(std::locale("")); // for C++
	//std::std::cout.imbue(std::locale());
	volebneUdaje.nacitajKandidatov();
	kandidati_ = volebneUdaje.getKandidati();
	for (const Kandidat* kandidat : kandidati_)
	{
		usporiadaniKandidati_.insert(kandidat->getCeleMeno(), kandidat);
	}

	volebneUdaje.nacitajKraje();
	kraje_ = volebneUdaje.getKraje();
	pripravSpecializovaneKolekcie(kraje_, usporiadaneKraje_);

	volebneUdaje.nacitajOkresy(usporiadaneKraje_);
	okresy_ = volebneUdaje.getOkresy();
	pripravSpecializovaneKolekcie(okresy_, usporiadaneOkresy_);

	volebneUdaje.nacitajObce(usporiadaneOkresy_);
	obce_ = volebneUdaje.getObce();
	pripravSpecializovaneKolekcie(obce_, usporiadaneObce_);

	setlocale(LC_ALL, "");
	std::cout << "*** Vitajte vo volebnom analyz·tore ***" << std::endl;

	bool pokracovat = true;
	do {
		zobrazMenu();
		std::string volba = ziskajVolbu();
		pokracovat = vykonajVolbu(volba);
	} while (pokracovat);
}