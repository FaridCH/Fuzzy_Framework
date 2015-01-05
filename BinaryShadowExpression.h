#ifndef BINARYSHADOWEXPRESSION_H
#define BINARYSHADOWEXPRESSION_H

#include "BinaryExpression.h"
#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class BinaryShadowExpression : public core::BinaryExpression<T>
	{
	public:
		BinaryShadowExpression(){};
		BinaryShadowExpression(core::BinaryExpression<T>* _target) : target(_target){};
		virtual ~BinaryShadowExpression(){};

		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;

		virtual core::BinaryExpression<T>* getTarget() const;

	private:
		core::BinaryExpression<T>* target;
	};

	template <class T>
	T BinaryShadowExpression<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		if(target!=NULL)
			return target->evaluate(l,r);
		else
			throw new core::NullExpressionException("target null");
	}

	template <class T>
	core::BinaryExpression<T>* BinaryShadowExpression<T>::getTarget() const
	{
		return target;
	}
}
#endif

