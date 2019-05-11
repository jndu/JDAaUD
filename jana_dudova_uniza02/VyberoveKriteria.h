#pragma once

#include <functional>
#include <cmath>

#include "structures/list/array_list.h"
#include "Kriteria.h"

template<typename O>
class VyberoveKriterium
{
public:
	virtual O* evaluate(const structures::ArrayList<O*>& objects) const = 0;
};

template<typename T, typename O>
class VyberoveKriteriumMinMax : public VyberoveKriterium<O>
{
protected:
	const Kriterium<T, O>& kriterium_;
	const std::function<bool(const T&, const T&)>& jeDruhyLepsi_;
public:
	VyberoveKriteriumMinMax(const Kriterium<T, O>& kriterium, const std::function<bool(const T&, const T&)>& jeDruhyLepsi) :
		kriterium_(kriterium), jeDruhyLepsi_(jeDruhyLepsi) {}

	O* evaluate(const structures::ArrayList<O*>& objects) const override
	{
		if (objects.size() == 0)
		{
			throw std::exception("Cannot pick element from empty collection");
		}
		else if (objects.size() == 1)
		{
			return objects[0];
		}
		else
		{
			O* najlepsi = objects[0];
			for (unsigned i = 1; i < objects.size(); i++)
			{
				if (jeDruhyLepsi_(kriterium_.evaluate(*najlepsi), kriterium_.evaluate(*objects[i])))
				{
					najlepsi = objects[i];
				}
			}
			return najlepsi;
		}
	}
};

template<typename T, typename O>
class VyberoveKriteriumMinimum : public VyberoveKriteriumMinMax<T, O>
{
public:
	VyberoveKriteriumMinimum(const Kriterium<T, O>& kriterium) :
		VyberoveKriteriumMinMax(kriterium,
			static_cast<std::function<bool(const T& najlepsi, const T& druhy)>>([](const T& najlepsi, const T& druhy) { return najlepsi > druhy; })) {}
};

template<typename T, typename O>
class VyberoveKriteriumMaximum : public VyberoveKriteriumMinMax<T, O>
{
public:
	VyberoveKriteriumMaximum(const Kriterium<T, O>& kriterium) :
		VyberoveKriteriumMinMax(kriterium,
			[](const T& najlepsi, const T& druhy) { return najlepsi < druhy; }) {}
};

class VyberoveKriteriumNajviacNajmenejHlasov : public VyberoveKriterium<UzemnaJednotka>
{
private:
	const Kandidat& kandidat_;
	const TypKola kolo_;
	const std::function<bool(int, int)> trebaZmenitNajlepsieho_;

public:
	VyberoveKriteriumNajviacNajmenejHlasov(const Kandidat& kandidat,
		const TypKola kolo,
		const std::function<bool(int, int)>& trebaZmenitNajlepsieho) :
		VyberoveKriterium(), kandidat_(kandidat), kolo_(kolo), trebaZmenitNajlepsieho_(trebaZmenitNajlepsieho) {}

	UzemnaJednotka* evaluate(const structures::ArrayList<UzemnaJednotka*>& objects) const override
	{
		if (objects.size() == 0)
		{
			throw std::exception("Cannot pick element from empty collection");
		}
		else if (objects.size() == 1)
		{
			return objects[0];
		}
		else
		{
			std::cout << "Budovanie vyberove kriteria najviac hlasov:" << std::endl;

			UzemnaJednotka* najlepsi = objects[0];
			for (unsigned i = 1; i < objects.size(); i++)
			{
				KriteriumHlasyZiskane kHlasyZiskaneNajlepsi(*najlepsi, kolo_);
				KriteriumHlasyZiskane kHlasyZiskane(*objects[i], kolo_);
				if (trebaZmenitNajlepsieho_(kHlasyZiskaneNajlepsi.evaluate(kandidat_), kHlasyZiskane.evaluate(kandidat_)))
				{
					najlepsi = objects[i];
				}
			}
			return najlepsi;
		}
	}
};

class VyberoveKriteriumNajviacHlasov : public VyberoveKriteriumNajviacNajmenejHlasov
{
public:
	VyberoveKriteriumNajviacHlasov(const Kandidat& kandidat, const TypKola kolo) :
		VyberoveKriteriumNajviacNajmenejHlasov(kandidat, kolo, [](const int& najlepsi, const int& iny) { return najlepsi < iny; }) {}
};

class VyberoveKriteriumNajmenejHlasov : public VyberoveKriteriumNajviacNajmenejHlasov
{
public:
	VyberoveKriteriumNajmenejHlasov(const Kandidat& kandidat, const TypKola kolo) :
		VyberoveKriteriumNajviacNajmenejHlasov(kandidat, kolo, [](const int& najlepsi, const int& iny) { return najlepsi > iny; }) {}
};

class VyberoveKriteriumNajstabilnejsieVysledky : VyberoveKriterium<UzemnaJednotka>
{
private:
	const Kandidat& kandidat1_;
	const TypKola kolo1_;
	const Kandidat& kandidat2_;
	const TypKola kolo2_;
public:
	VyberoveKriteriumNajstabilnejsieVysledky(const Kandidat& kandidat1, const TypKola kolo1,
		const Kandidat& kandidat2, const TypKola kolo2) :
		VyberoveKriterium(), kandidat1_(kandidat1), kolo1_(kolo1), kandidat2_(kandidat2), kolo2_(kolo2) {}

	UzemnaJednotka* evaluate(const structures::ArrayList<UzemnaJednotka*>& objects) const override
	{
		if (objects.size() == 0)
		{
			throw std::exception("Cannot pick element from empty collection");
		}
		else if (objects.size() == 1)
		{
			return objects[0];
		}
		else
		{
			UzemnaJednotka* najlepsi = objects[0];
			for (unsigned i = 1; i < objects.size(); i++)
			{
				KriteriumHlasyZiskane kHlasyZiskaneNajlepsiK1(*najlepsi, kolo1_);
				KriteriumHlasyZiskane kHlasyZiskaneNajlepsiK2(*najlepsi, kolo2_);
				auto rozdielNajlepsi = std::abs(kHlasyZiskaneNajlepsiK1.evaluate(kandidat1_) - kHlasyZiskaneNajlepsiK2.evaluate(kandidat2_));

				KriteriumHlasyZiskane kHlasyZiskaneK1(*objects[i], kolo1_);
				KriteriumHlasyZiskane kHlasyZiskaneK2(*objects[i], kolo2_);
				auto rozdiel = std::abs(kHlasyZiskaneK1.evaluate(kandidat1_) - kHlasyZiskaneK2.evaluate(kandidat2_));

				if (rozdielNajlepsi > rozdiel)
				{
					najlepsi = objects[i];
				}
			}
			return najlepsi;
		}
	}
};