#ifndef AGGMAX_H
#define AGGMAX_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy
{

	template <class T>
	class AggMax : public Agg<T>
	{
	public :
		AggMax(){};
		virtual ~AggMax(){};
	
		T evaluate(core::Expression<T>* , core::Expression<T>*) const;
	};

	template <class T>
	T AggMax<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const{
		T lAggMax = l->evaluate();
		T rAggMax = r->evaluate();
		return (lAggMax >= rAggMax) ? lAggMax : rAggMax;
	}
}
#endif