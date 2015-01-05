#ifndef UNARYEXPRESSIONMODEL_H
#define UNARYEXPRESSIONMODEL_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace core
{
	template <class T>
	class UnaryExpressionModel: public UnaryExpression<T>, public Expression<T>
	{
	public:
		UnaryExpressionModel() {};
		UnaryExpressionModel(UnaryExpression<T>* ope, Expression<T>* operand): ope(ope), operand(operand) {};
		virtual ~UnaryExpressionModel() {};

		virtual T evaluate() const;
		virtual T evaluate(Expression*) const;

		virtual Expression<T>* getOperand();
		virtual UnaryExpression<T>* getOperator();
		virtual void setOperand(Expression<T>*);
		virtual void setOperator(UnaryExpression<T>*);

	private:
		UnaryExpression<T>* ope;
		Expression<T>* operand;
	};

	template <class T>
	T UnaryExpressionModel<T>::evaluate() const
	{
		if (operand == NULL)
			throw new NullExpressionException("operand null");

		return evaluate(operand);
	}

	template <class T>
	T UnaryExpressionModel<T>::evaluate(Expression<T>* o) const
	{
		if (ope == NULL)
			throw new NullExpressionException("ope null");

		return ope->evaluate(o);
	}

	template <class T>
	void UnaryExpressionModel<T>::setOperator(UnaryExpression<T>* une)
	{
		ope=une;
	}

	template <class T>
	void UnaryExpressionModel<T>::setOperand(Expression<T>* o)
	{
		operand=o;
	}

	template <class T>
	Expression<T>* UnaryExpressionModel<T>::getOperand()
	{
		return operand;
	}

	template <class T>
	UnaryExpression<T>* UnaryExpressionModel<T>::getOperator()
	{
		return ope;
	}
}

#endif