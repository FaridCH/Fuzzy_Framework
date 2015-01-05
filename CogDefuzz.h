#ifndef COGDEFUZZ_H
#define COGDEFUZZ_H

#include <vector>
#include <numeric>
#include "MamdaniDefuzz.h"

namespace fuzzy
{
	template <class T>
	class CogDefuzz: public MamdaniDefuzz<T>
	{
	public:
		CogDefuzz() {};
		~CogDefuzz() {};

	protected:
		virtual T defuzz(const Shape&) const;
	};

	template <class T>
	T CogDefuzz<T>::defuzz(const Shape& s) const
	{
		std::vector<T> product;
		std::vector<T>::const_iterator itX = s.first.begin();
		std::vector<T>::const_iterator itY = s.second.begin();
		

		for (; itY != s.second.end(); ++itY, ++itX)
			product.push_back(*itX * *itY);

		T sumProduct = 0;
		T sumY = 0;

		return std::accumulate(product.begin(), product.end(), sumProduct) / std::accumulate(s.second.begin(), s.second.end(), sumY); // somme des xi*yi/somme des yi
	}
}

#endif
