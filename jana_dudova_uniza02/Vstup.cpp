#include "Vstup.h"

void Vstup::zapniLocaleVstup()
{
	stareKodovanie = GetConsoleCP();
	SetConsoleCP(1250);
}

void Vstup::vypniLocaleVstup()
{
	SetConsoleCP(stareKodovanie);
}

std::string Vstup::ziskajRetazec(const std::string& text)
{
	static const std::function<bool(std::string)> podmienka = [](const std::string&) { return true; };
	return ziskajVstupSPodmienkou(podmienka, text);
}

int Vstup::ziskajNezaporneCeleCislo(const std::string& text/* = ""*/)
{
	static const std::function<bool(int)> podmienka = [](int cislo) { return cislo >= 0; };
	return ziskajVstupSPodmienkou(podmienka, text.empty() ? "Zadaj nezáporné celé èíslo: " : text);
}

double Vstup::ziskajPercent(const std::string& text/* = ""*/)
{
	static const std::function<bool(double)> podmienka = [](double cislo) { return cislo >= 0.0 && cislo <= 100.0; };
	return ziskajVstupSPodmienkou(podmienka, text.empty() ? "Zadaj èíslo z intervalu <0.0, 100.0>: " : text);
}