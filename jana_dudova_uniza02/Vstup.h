#pragma once

#include <functional>
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <limits>

class Vstup
{
private:
	UINT stareKodovanie = 852;

	void zapniLocaleVstup();
	void vypniLocaleVstup();

public:
	template<typename T>
	T ziskajVstupSPodmienkou(const std::function<bool(T)>& predikat, const std::string& text)
	{
		T hodnota;
		do {
			std::cout << text;
			std::cin >> hodnota;
		} while (!predikat(hodnota));

		// aby sme sa zbavili znaku noveho riadka vo vstupnom bufferi
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

		return hodnota;
	}

	template<>
	std::string ziskajVstupSPodmienkou<std::string>(const std::function<bool(std::string)>& predikat, const std::string& text)
	{
		std::string hodnota;
		do {
			std::cout << text;
			zapniLocaleVstup();
			getline(std::cin, hodnota);
			vypniLocaleVstup();
		} while (!predikat(hodnota));

		return hodnota;
	}

	std::string ziskajRetazec(const std::string& text);
	int ziskajNezaporneCeleCislo(const std::string& text = "");
	double ziskajPercent(const std::string& text = "");
};
