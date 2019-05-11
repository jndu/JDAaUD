#pragma once

#include <string>
#include <locale>
#include <clocale>

#include "structures/list/array_list.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/table.h"

#include "Kandidat.h"
#include "Kolo.h"
#include "UzemnaJednotka.h"
#include "VyssiCelok.h"
#include "Kraj.h"
#include "Okres.h"
#include "Obec.h"
#include "Vstup.h"
#include "VolebneUdaje.h"
#include "Kriteria.h"
#include "Filtre.h"
#include "VyberoveKriteria.h"

class VolebnyAnalyzator
{
private:
	Vstup vstup;
	VolebneUdaje volebneUdaje;

	structures::ArrayList<Kandidat*> kandidati_;
	structures::ArrayList<Obec*> obce_;
	structures::ArrayList<Okres*> okresy_;
	structures::ArrayList<Kraj*> kraje_;

	structures::ArrayList<UzemnaJednotka*> uzemneJednotky_;

	structures::SortedSequenceTable<std::string, const Kandidat*> usporiadaniKandidati_;
	structures::SortedSequenceTable<int, Obec*> usporiadaneObce_;
	structures::SortedSequenceTable<int, Okres*> usporiadaneOkresy_;
	structures::SortedSequenceTable<int, Kraj*> usporiadaneKraje_;

	template<typename T>
	void pripravSpecializovaneKolekcie(const structures::ArrayList<T*>& objekty,
		structures::SortedSequenceTable<int, T*>& usporiadaneObjekty)
	{
		for (T* objekt : objekty)
		{
			usporiadaneObjekty.insert(objekt->getKod(), objekt);
			uzemneJednotky_.add(objekt);
		}
	}

	void pripravStruktury();

	template<typename T>
	void uvolniArrayList(structures::ArrayList<T*>& arrayList)
	{
		for (T* item : arrayList)
		{
			delete item;
		}
	}

	void zobrazMenu();
	std::string ziskajVolbu();
	bool vykonajVolbu(const std::string& volba);

	// hladanie v kolekciach

	const VyssiCelok* najdiVyssiCelokPodlaKodu(const int kod);
	const UzemnaJednotka* najdiUzemnuJednotkuPodlaKodu(const int kod);
	const Kandidat* najdiKandidataPodlaMena(const std::string& menoAPriezvisko);

	// vyber objektov uzivatelom

	const VyssiCelok* vyberVyssiCelok();
	const Kandidat* vyberKandidata();
	const UzemnaJednotka* vyberUzemnuJednotku();
	TypKola vyberLenJednoKolo();
	TypKola vyberKolo();

	// tvorba kriterii

	KriteriumPrislusnostObce vytvorKriteriumPrislusnostObce();
	KriteriumVolici vytvorKriteriumVolici();
	KriteriumVydaneObalky vytvorKriteriumVydaneObalky();
	KriteriumUcast vytvorKriteriumUcast();
	KriteriumOdovzdaneObalky vytvorKriteriumOdovzdaneObalky();
	KriteriumHlasyOdovzdane vytvorKriteriumHlasyOdovzdane();
	KriteriumHlasyZiskane vytvorKriteriumHlasyZiskane();
	KriteriumPlatneHlasy vytvorKriteriumPlatneHlasy();

	// tvorba filtrov

	FilterNazov vytvorFilterNazov(const KriteriumNazov& kriteriumNazov);
	FilterVolici vytvorFilterVolici(const KriteriumVolici& kriteriumVolici);
	FilterUcast vytvorFilterUcast(const KriteriumUcast& kriteriumUcast);
	FilterMeno vytvorFilterMeno(const KriteriumMeno& kriteriumMeno);

	// pomocne metody k filtrom

	template<typename T, typename O, typename Result>
	structures::ArrayList<Result*> pouziFilter(const structures::ArrayList<Result*>& objekty, const Filter<T, O>& filter)
	{
		structures::ArrayList<Result*> result;
		for (Result* objekt : objekty)
		{
			if (filter.evaluate(*objekt))
			{
				result.add(objekt);
			}
		}
		return result;
	}

	// akcie z menu

	void vypisInformacieOObciach();

	template<typename A, typename B>
	struct MyPair
	{
		A first;
		B second;

		bool operator==(const MyPair<A, B>& rhs) const
		{
			return first == rhs.first;
		}
	};

	template<typename T>
	void vypisObceZoradenePodlaKriteria(const structures::ArrayList<MyPair<T, std::string>*>& zoradeneObce)
	{
		for (const auto item : zoradeneObce)
		{
			std::cout << item->first << "; " << item->second << std::endl;
		}
	}

	// source https://stackoverflow.com/questions/11196571/quick-sort-sorts-descending-not-ascending
	template<typename K, typename T>
	void quicksortAscending(structures::ArrayList<MyPair<K, T>*>& A, int p, int r) {
		if (p < r) {
			int q = partitionAscending(A, p, r);
			quicksortAscending(A, p, q);
			quicksortAscending(A, q + 1, r);
		}
	}

	template<typename K, typename T>
	int partitionAscending(structures::ArrayList<MyPair<K, T>*>& A, int p, int r) {
		K x = A[p]->first; // pivot
		int i = p;
		int j = r;
		while (true) {
			while (A[i]->first < x) {
				i++;
			}

			while (A[j]->first > x) {
				j--;
			}
			if (i < j) {
				swap(A[i], A[j]);
				i++;
				j--;
			}
			else {
				return j;
			}
		}
	}

	template<typename K, typename T>
	void quicksortDescending(structures::ArrayList<MyPair<K, T>*>& A, int p, int r) {
		if (p < r) {
			int q = partitionDescending(A, p, r);
			quicksortDescending(A, p, q);
			quicksortDescending(A, q + 1, r);
		}
	}

	template<typename K, typename T>
	int partitionDescending(structures::ArrayList<MyPair<K, T>*>& A, int p, int r) {
		K x = A[p]->first; // pivot
		int i = p;
		int j = r;
		while (true) {
			while (A[i]->first > x) {
				i++;
			}

			while (A[j]->first < x) {
				j--;
			}
			if (i < j) {
				swap(A[i], A[j]);
				i++;
				j--;
			}
			else {
				return j;
			}
		}
	}

	template<typename K, typename T>
	void zoradVzostupne(structures::ArrayList<MyPair<K, T>*>& A)
	{
		if (A.size() == 0)
		{
			return;
		}
		quicksortAscending(A, 0, A.size() - 1);
	}

	template<typename K, typename T>
	void zoradZostupne(structures::ArrayList<MyPair<K, T>*>& A)
	{
		if (A.size() == 0)
		{
			return;
		}
		quicksortDescending(A, 0, A.size() - 1);
	}

	template<typename T, typename O, typename V>
	void zoradAVypisObcePodlaKriteria(const structures::ArrayList<V*>& obce, const Kriterium<T, O>& kriterium)
	{
		// TableItem sa nedal pouzit lebo nema operator==
		structures::ArrayList<MyPair<T, std::string>*> nazvyObci;
		for (const auto* obec : obce)
		{
			auto myPair = new MyPair<T, std::string>();
			myPair->first = kriterium.evaluate(*obec);
			myPair->second = obec->getNazov();
			nazvyObci.add(myPair);
		}

		std::cout << "Vzostupne:" << std::endl;
		zoradVzostupne(nazvyObci);
		vypisObceZoradenePodlaKriteria(nazvyObci);
		std::cout << "Zostupne:" << std::endl;
		zoradZostupne(nazvyObci);
		vypisObceZoradenePodlaKriteria(nazvyObci);

		uvolniArrayList(nazvyObci);
	}

	void zoradenieObci();
	void vypisanieInformaciiOUzemnychJednotkach();
	void zoradenieUzemnychJednotiekSplnajucichDanyFilter();
	void vypisanieVysledkovKandidataVUzemnejJednotke();
	void zoradenieKandidatovPodlaVysledkovVUzemnychJednotkach();
	void vypisanieVyberovychKriterii();

public:
	void spusti();
};