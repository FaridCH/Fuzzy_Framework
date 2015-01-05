#ifndef ISTRIANGLE_H
#define ISTRIANGLE_H

#include "UnaryExpression.h"
#include "Expression.h"
#include "Is.h"

namespace fuzzy
{
	template <class T>
	class IsTriangle: public Is<T>
	{
	public:
		IsTriangle(){};
		IsTriangle(T _min, T _mid, T _max): min(_min), mid(_mid), max(_max) {};
		virtual ~IsTriangle(){};
		virtual T evaluate(core::Expression<T>*) const;

	private:
		T min, mid, max;
	};

	template <class T>
	T IsTriangle<T>::evaluate (core::Expression<T>* o) const
	{
		T val = o->evaluate();
		if(val > min && val < mid)
			return (val - min) / (mid - min);
		if (val == mid)
			return 1;
		if(val > mid && val < max)
			return (max - val) / (max - mid);
		
		return 0;
	}
}

#endif