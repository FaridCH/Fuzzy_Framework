#ifndef UNARYSHADOWEXPRESSION_H
#define UNARYSHADOWEXPRESSION_H

#include "UnaryExpression.h"
#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class UnaryShadowExpression : public core::UnaryExpression<T>
	{
	public:
		UnaryShadowExpression(){};
		UnaryShadowExpression(core::UnaryExpression<T>* _target) : target(_target){};
		virtual ~UnaryShadowExpression(){};

		T evaluate(core::Expression<T>*) const;
	
	private:
		core::UnaryExpression<T>* target;
	};

	template <class T>
	T UnaryShadowExpression<T>::evaluate(core::Expression<T>* o) const
	{
		if (target!=NULL)
			return target->evaluate(o);
		else
			throw new core::NullExpressionException("target null");
	}
}
#endif