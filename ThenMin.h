#ifndef THENMIN_H
#define THENMIN_H

#include "Then.h"
#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class ThenMin : public Then<T>
	{
	public:
		ThenMin(){};
		virtual ~ThenMin(){};

		T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMin<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lThenMin = l->evaluate();
		T rThenMin = r->evaluate();
		return (lThenMin <= rThenMin) ? lThenMin : rThenMin;
	}

}

#endif