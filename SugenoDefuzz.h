#ifndef SUGENODEFUZZ_H
#define SUGENODEFUZZ_H

#include "NaryExpression.h"

namespace fuzzy
{
    template <class T>
    class SugenoDefuzz : public core::NaryExpression<T>
    {
    public:
        SugenoDefuzz() {};
        virtual ~SugenoDefuzz() {};

        virtual T evaluate(std::vector<core::Expression<T>*>* operands) const;
    };

    template <class T>
    T SugenoDefuzz<T>::evaluate(std::vector<core::Expression<T>*>* operands) const
    {
		std::vector<core::Expression<T>*>::iterator it;

		T num = 0;
		T denum = 0;

		// calcul somme des wi
		for (it = operands->begin(); it != operands->end(); it++)
		{
			core::BinaryExpressionModel<T>*  bem = (core::BinaryExpressionModel<T>*)  (*it);
			BinaryShadowExpression<T>* bse = (BinaryShadowExpression<T>*) bem->getOpe();
			SugenoThen<T>*             sth = (SugenoThen<T>*)             bse->getTarget();

			num   += (*it)->evaluate();
			denum += sth->getPremiseValue();
		}

		if (denum != 0)
			return num/denum;
		else
			return 0;
    }
}

#endif
