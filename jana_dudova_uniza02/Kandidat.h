#pragma once

#include <string>

class Kandidat
{
private:
	int poradoveCislo1_;
	int poradoveCislo2_ = -1;
	std::string meno_;
	std::string priezvisko_;

public:
	int getPoradoveCislo1() const;
	int getPoradoveCislo2() const;
	std::string getMeno() const;
	std::string getPiezvisko() const;
	std::string getCeleMeno() const;

	void setPoradoveCislo1(int poradoveCislo1);
	void setPoradoveCislo2(int poradoveCislo2);
	void setMeno(const std::string& meno);
	void setPriezvisko(const std::string& priezvisko);
};