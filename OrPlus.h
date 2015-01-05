#ifndef ORPLUS_H
#define ORPLUS_H

#include "Or.h"
#include "Expression.h"

namespace fuzzy
{
	
	template<class T>
	class OrPlus : public Or<T>
	{
	public:
		OrPlus(){};
		virtual ~OrPlus(){};

		T evaluate(core::Expression<T>* , core::Expression<T>*) const;
	};

	template <class T>
	T OrPlus<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T rOrPlus = r->evaluate();
		T lOrPlus = l->evaluate();
		return rOrPlus+lOrPlus;
	}
}
#endif