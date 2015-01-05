#ifndef AGGPLUS_H
#define AGGPLUS_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy
{
	
	template<class T>
	class AggPlus : public Agg<T>
	{
	public:
		AggPlus(){};
		virtual ~AggPlus(){};

		T evaluate(core::Expression<T>* , core::Expression<T>*) const;
	};

	template <class T>
	T AggPlus<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T rAggPlus = r->evaluate();
		T lAggPlus = l->evaluate();
		return rAggPlus+lAggPlus;
	}
}
#endif