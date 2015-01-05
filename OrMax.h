#ifndef ORMAX_H
#define ORMAX_H

#include "Or.h"
#include "Expression.h"

namespace fuzzy
{

	template <class T>
	class OrMax : public Or<T>
	{
	public :
		OrMax(){};
		virtual ~OrMax(){};
	
		T evaluate(core::Expression<T>* , core::Expression<T>*) const;
	};

	template <class T>
	T OrMax<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const{
		T lOrMax = l->evaluate();
		T rOrMax = r->evaluate();
		return (lOrMax >= rOrMax) ? lOrMax : rOrMax;
	}
}
#endif