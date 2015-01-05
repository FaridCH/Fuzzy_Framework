#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "NaryExpressionModel.h"
#include <vector>

namespace core
{
	template <class T>
	class ExpressionFactory
	{
	public:
		typedef std::vector<Expression<T>*> Memory;

		ExpressionFactory() {};
		~ExpressionFactory();

		UnaryExpressionModel<T>* newUnary(UnaryExpression<T>*, Expression<T>*);
		BinaryExpressionModel<T>* newBinary(BinaryExpression<T>*, Expression<T>*, Expression<T>*);
		NaryExpressionModel<T>* newNary(NaryExpression<T>*, std::vector<Expression<T>*>*);
		Expression<T>* hold(Expression<T>*);

	private:
		Memory memory;
	};

	template <class T>
	ExpressionFactory<T>::~ExpressionFactory()
	{
		for (Memory::iterator it = memory.begin(); it != memory.end(); it++)
			delete *it;
	}

	template <class T>
	UnaryExpressionModel<T>* ExpressionFactory<T>::newUnary(UnaryExpression<T>* ope, Expression<T>* o)
	{
		return (UnaryExpressionModel<T>*) hold(new UnaryExpressionModel<T>(ope, o));
	}

	template <class T>
	BinaryExpressionModel<T>* ExpressionFactory<T>::newBinary(BinaryExpression<T>* ope, Expression<T>* l, Expression<T>* r)
	{
		return (BinaryExpressionModel<T>*) hold(new BinaryExpressionModel<T>(ope, l, r));
	}

	template <class T>
	NaryExpressionModel<T>* ExpressionFactory<T>::newNary(NaryExpression<T>* ope, std::vector<Expression<T>*>* operands)
	{
		return (NaryExpressionModel<T>*) hold(new NaryExpressionModel<T>(ope, operands));
	}

	template <class T>
	Expression<T>* ExpressionFactory<T>::hold(Expression<T>* e)
	{
		memory.push_back(e);
		return e;
	}
}

#endif
