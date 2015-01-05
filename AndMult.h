#ifndef ANDMULT_H
#define ANDMULT_H

#include "Expression.h"
#include "And.h"

namespace fuzzy
{
	template <class T>
	class AndMult: public And<T>
	{
	public:
		AndMult() {};
		virtual ~AndMult() {};
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T AndMult<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lmult = l->evaluate();
		T rmult = r->evaluate();
		return lmult*rmult;
	}
}

#endif