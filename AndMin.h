#ifndef ANDMIN_H
#define ANDMIN_H

#include "Expression.h"
#include "And.h"

namespace fuzzy
{
	template <class T>
	class AndMin: public And<T>
	{
	public:
		AndMin() {};
		virtual ~AndMin() {};
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T AndMin<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lAndMin = l->evaluate();
		T rAndMin = r->evaluate();
		return (lAndMin<=rAndMin)? lAndMin : rAndMin;
	}
}

#endif