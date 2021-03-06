#ifndef SUGENOCONCLUSION_H
#define SUGENOCONCLUSION_H

#include "NaryExpression.h"

namespace fuzzy
{
    template <class T>
    class SugenoConclusion : public core::NaryExpression<T>
    {
    public:
		SugenoConclusion(std::vector<T>* coeff):coeff(coeff) {};
        virtual ~SugenoConclusion() {};

        virtual T evaluate(std::vector<core::Expression<T>*>* operands) const;

    private:
		std::vector<T> *coeff;
    };

    template <class T>
    T SugenoConclusion<T>::evaluate(std::vector<core::Expression<T>*>* operands) const
    {
		std::vector<T>::const_iterator itcoef = coeff->begin();
		std::vector<core::Expression<T>*>::const_iterator itexpr = operands->begin();
		T z = 0;

		// calcul de la somme des Zi
		for (; itexpr != operands->end() && itcoef != coeff->end(); itexpr++, itcoef++)
		{
			// evaluation de la r�gle courante
			T eval = (*itexpr)->evaluate();

			// multiplication par le coefficient associ� � cette r�gle
			z += (*itcoef) * eval;
		}

		return z;
    }
}

#endif
