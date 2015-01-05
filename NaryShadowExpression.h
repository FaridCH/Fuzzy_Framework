#ifndef NARYSHADOWEXPRESSION_H
#define NARYSHADOWEXPRESSION_H

#include "NaryExpression.h"

namespace fuzzy
{
	template <class T>
	class NaryShadowExpression : public core::NaryExpression<T>
	{
	public:
		NaryShadowExpression() {};
		NaryShadowExpression(core::NaryExpression<T>* t):target(t) {};
		virtual ~NaryShadowExpression() {};

		void setTarget(core::NaryExpression<T>*);
		virtual core::NaryExpression<T>* getTarget();
		T evaluate(std::vector<core::Expression<T>*>* operands) const;

	private:
		core::NaryExpression<T>* target;
	};

	template <class T>
	void NaryShadowExpression<T>::setTarget(core::NaryExpression<T>* t)
	{
		target = t;
	}

	template <class T>
	core::NaryExpression<T>* NaryShadowExpression<T>::getTarget()
	{
		return target;
	}

	template <class T>
	T NaryShadowExpression<T>::evaluate(std::vector<core::Expression<T>*>* operands) const
	{
		if (target == NULL)
			throw new NullExpressionException("target null");
			
		return target->evaluate(operands);
	}

}

#endif