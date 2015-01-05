#ifndef SUGENOTHEN_H
#define SUGENOTHEN_H

#include "Then.h"

namespace fuzzy
{
    template <class T>
    class SugenoThen : public Then<T>
    {
    public:
		SugenoThen():premiseValue(0) {};
        virtual ~SugenoThen() {};

        virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
        virtual T getPremiseValue();

    public:
        mutable T premiseValue;
    };

    template <class T>
    T SugenoThen<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const
    {
        premiseValue = l->evaluate();

		return premiseValue * r->evaluate();
    }

    template <class T>
    T SugenoThen<T>::getPremiseValue()
    {
        return premiseValue;
    }
}

#endif
