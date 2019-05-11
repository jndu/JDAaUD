#pragma once

#include "Kriteria.h"

template<typename T, typename O>
class Filter
{
private:
	const Kriterium<T, O>& criterion_;

	virtual bool evaluate(const O& object, const Kriterium<T, O>& criterion) const = 0;
public:
	Filter(const Kriterium<T, O>& criterion) :
		criterion_(criterion) {}

	virtual bool evaluate(const O& object) const { return evaluate(object, criterion_); }
};

template<typename T, typename O>
class Filter_fi : public Filter<T, O>
{
private:
	T alpha_;

	bool evaluate(const O& object, const Kriterium<T, O>& criterion) const override
	{
		return criterion.evaluate(object) == alpha_;
	}
public:
	Filter_fi(const Kriterium<T, O>& criterion, const T& alpha) :
		Filter(criterion), alpha_(alpha) {}
};

template<typename T, typename O>
class Filter_FI : public Filter<T, O>
{
private:
	T alpha_;
	T beta_;
public:
	Filter_FI(const Kriterium<T, O>& criterion, const T& alpha, const T& beta) :
		Filter(criterion), alpha_(alpha), beta_(beta) {}

	bool evaluate(const O& object, const Kriterium<T, O>& criterion) const override
	{
		T value = criterion.evaluate(object);
		return value >= alpha_ && value <= beta_;
	}
};

class FilterNazov : public Filter_fi<std::string, UzemnaJednotka>
{
public:
	FilterNazov(const Kriterium<std::string, UzemnaJednotka>& criterion, const std::string& nazov) :
		Filter_fi(criterion, nazov) {}
};

class FilterVolici : public Filter_FI<int, UzemnaJednotka>
{
public:
	FilterVolici(const Kriterium<int, UzemnaJednotka>& criterion, const int minimalneVolicov, const int maximalneVolicov) :
		Filter_FI(criterion, minimalneVolicov, maximalneVolicov) {}
};

class FilterUcast : public Filter_FI<double, UzemnaJednotka>
{
public:
	FilterUcast(const Kriterium<double, UzemnaJednotka>& kriterium, const double minimalnaUcast, const double maximalnaUcast) :
		Filter_FI(kriterium, minimalnaUcast, maximalnaUcast) {}
};

class FilterPrislusnostObce : public Filter_fi<bool, Obec>
{
public:
	FilterPrislusnostObce(const Kriterium<bool, Obec>& kriterium) :
		Filter_fi(kriterium, true) {}
};

class FilterMeno : public Filter_fi<std::string, Kandidat>
{
public:
	FilterMeno(const Kriterium<std::string, Kandidat>& kriterium, const std::string& meno) :
		Filter_fi(kriterium, meno) {}
};
