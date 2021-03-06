#ifndef NARYEXPRESSIONMODEL_H
#define NARYEXPRESSIONMODEL_H

#include "NaryExpression.h"

namespace core
{
	template <class T>
	class NaryExpressionModel: public NaryExpression<T>, public Expression<T>
	{
	public:
		NaryExpressionModel() {};
		NaryExpressionModel(NaryExpression<T>* operateur, std::vector<Expression<T>*>* operandes):operateur(operateur), operandes(operandes) {};
		virtual ~NaryExpressionModel() {};

		virtual T evaluate() const;
		virtual T evaluate(std::vector<Expression<T>*>*) const;

	private:
		NaryExpression<T>* operateur;
		std::vector<Expression<T>*>* operandes;
	};

	template <class T>
	T NaryExpressionModel<T>::evaluate() const
	{
		if (operandes->empty()) 
			throw new NullExpressionException("operandes vector empty");

		return evaluate(operandes);
	}

	template <class T>
	T NaryExpressionModel<T>::evaluate(std::vector<Expression<T>*>* operands) const
	{
		if (operateur == NULL)
			throw new NullExpressionException("ope null");

		return operateur->evaluate(operands);
	}
}

#endif
