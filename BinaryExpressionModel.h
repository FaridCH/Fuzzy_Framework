#ifndef BINARYEXPRESSIONMODEL_H
#define BINARYEXPRESSIONMODEL_H

#include "Expression.h"
#include "BinaryExpression.h"

namespace core
{
	template <class T>
	class BinaryExpressionModel: public BinaryExpression<T>, public Expression<T>
	{
	public:
		BinaryExpressionModel() {};
		BinaryExpressionModel(BinaryExpression<T>* _ope, Expression<T>* _left, Expression<T>* _right): ope(_ope), left(_left), right(_right) {};
		virtual ~BinaryExpressionModel() {};
		
		virtual T evaluate() const;
		virtual T evaluate(Expression<T>*, Expression<T>*) const;
		BinaryExpression<T>* getOpe() const;
		void setOpe(BinaryExpression<T>*);

	private:
		BinaryExpression<T>* ope;
		Expression<T>* left;
		Expression<T>* right;
	};

	template <class T>
	T BinaryExpressionModel<T>::evaluate(Expression<T>* l, Expression<T>* r) const
	{
		if (ope == NULL)
			throw new NullExpressionException("ope null");

		return ope->evaluate(l, r);
	}

	template <class T>
	T BinaryExpressionModel<T>::evaluate() const
	{
		if (left == NULL)
			throw new NullExpressionException("left null");

		if (right == NULL)
			throw new NullExpressionException("right null");

		return evaluate(left, right);
	}
	
	template <class T>
	BinaryExpression<T>* BinaryExpressionModel<T>::getOpe() const
	{
		return ope;
	}
	
	template <class T>
	void BinaryExpressionModel<T>::setOpe(BinaryExpression<T>* _ope)
	{
		ope = _ope;
	}
}

#endif
