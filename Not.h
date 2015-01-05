#ifndef NOT_H
#define NOT_H

#include "UnaryExpression.h"
#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class Not : public core::UnaryExpression<T>
	{
	public:
		Not(){};
		virtual ~Not(){};

		T evaluate(core::Expression<T>*) const = 0;
	};

}

#endif