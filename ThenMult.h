#ifndef THENMULT_H
#define THENMULT_H

#include "Then.h"
#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class ThenMult : public Then<T>
	{
	public:
		ThenMult(){};
		virtual ~ThenMult(){};

		T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMult<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lThenMult = l->evaluate();
		T rThenMult = r->evaluate();
		return lThenMult*rThenMult;
	}

}

#endif