#ifndef NARYEXPRESSION_H
#define NARYEXPRESSION_H

#include <vector>
#include "Expression.h"

namespace core
{
	template <class T>
	class NaryExpression
	{
	public:
		NaryExpression() {};
		virtual ~NaryExpression() {};

		virtual T evaluate(std::vector<Expression<T>*>*) const = 0;
	};
}

#endif