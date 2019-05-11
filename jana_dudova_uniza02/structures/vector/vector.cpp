#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)//parametricky konstruktor, taka ista pamat ako other, uz mam vytvoreny pamatovy priestor
	{
		//ked pouzijem calloc, alokuje volne pamatove miesto, mozem pouzit memcopy
		memory_ = memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_); // uvolnenie pamate
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const //klonovanie, vratenie objektu pri vzniku kopirovacieho konstruktora
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other) //operator priradenia; nikdy nepriradujem sam do seba
	{
		if (this != &other)
		{
			size_ = other.size_; //zmenime velkost
			memory_ = realloc(memory_, size_); //realokujeme
			memory_ = memcpy(memory_, other.memory_, size_); //nakopirujeme
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		// musia sa rovnat velkostou a obsahom
		return size_ == other.size_ && memcmp(memory_, other.memory_, size_) == 0;
	}

	byte& Vector::operator[](const int index)//spristupnuje byte odkazom &
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); // skontrolovania indexu, ak nie je v poriadku, vyhodi vynimku
		return *(reinterpret_cast<byte*>(memory_) + index); // pretypovanie smerniku void na smernik na byte a posuniem o index
	}

	byte Vector::operator[](const int index) const //spristupnuje hodnotou 
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); // skontrolovania indexu, ak nie je v poriadku, vyhodi vynimku
		return *(reinterpret_cast<byte*>(memory_) + index);
		
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		DSRoutines::rangeCheckExcept(index + count, size_, "Invalid end index!");

		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length != 0)
		{
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index in Vector src!");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid index in Vector dest!");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid end index in Vector src!");// 4+3<7 + 1
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid end index in Vector dest!");

			if (src == dest && (srcStartIndex + length <= destStartIndex || destStartIndex + length <= srcStartIndex))
			{
				memmove(src.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length); //memmove alokuje docasne miesto
			}
			else
			{
				memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);// rychle ale nepouziva sa pri prekryvani pamate
			}
		}
	}

	byte* Vector::getBytePointer(const int index) const // vrati byte s adresou
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); 
		return reinterpret_cast<byte*>(memory_) + index;//pretypovanie smernika a posuniem o index
	}

}