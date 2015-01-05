#ifndef NOTMINUS1_H
#define NOTMINUS1_H

#include "Not.h"
#include "Expression.h"
#include "UnaryExpression.h"

namespace fuzzy
{
	template <class T>
	class NotMinus1 : public Not<T>
	{
	public: 
		NotMinus1(){};
		virtual ~NotMinus1(){};

		T evaluate(core::Expression<T>*) const;
	};

	template <class T>
	T NotMinus1<T>::evaluate(core::Expression<T>* o) const
	{
		T minus = (o->evaluate());
		return (1-minus);
	}
}

#endif