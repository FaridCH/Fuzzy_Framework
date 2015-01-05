#ifndef FUZZYFACTORY_H
#define FUZZYFACTORY_H

#include "ExpressionFactory.h"
#include "Is.h"
#include "Not.h"
#include "And.h"
#include "Or.h"
#include "Then.h"
#include "Agg.h"
#include "SugenoConclusion.h"

#include "MamdaniDefuzz.h"
#include "SugenoDefuzz.h"

#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "NaryShadowExpression.h"

using namespace core;

namespace fuzzy
{
	template <class T>
	class FuzzyFactory: public ExpressionFactory<T>
	{
	public:
		FuzzyFactory() {};
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MamdaniDefuzz<T>*);
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MamdaniDefuzz<T>*, SugenoDefuzz<T>*, SugenoConclusion<T>*);
		virtual ~FuzzyFactory();
		
		virtual core::Expression<T>* newNot(core::Expression<T>*);
		virtual core::Expression<T>* newAnd(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newOr(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newThen(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newAgg(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newDefuzz(core::Expression<T>*, core::Expression<T>*, const T&, const T&, const T&);
		virtual core::Expression<T>* newIs(Is<T>*, core::Expression<T>*);
        virtual core::Expression<T>* newSugeno(std::vector<core::Expression<T>*>*);
        virtual core::Expression<T>* newNConclusion(std::vector<core::Expression<T>*>*);

		void changeNot(Not<T>*);
		void changeAnd(And<T>*);
		void changeOr(Or<T>*);
		void changeThen(Then<T>*);
		void changeAgg(Agg<T>*);
		void changeDefuzz(MamdaniDefuzz<T>*);
		void changeSugeno(SugenoDefuzz<T>*);
		void changeConclusion(SugenoConclusion<T>*);

	private:
		UnaryShadowExpression<T>*  not;
		BinaryShadowExpression<T>* and;
		BinaryShadowExpression<T>* or;
		BinaryShadowExpression<T>* then;
		BinaryShadowExpression<T>* agg;
		BinaryShadowExpression<T>* defuzz;
        NaryShadowExpression<T>*   sugeno;
        NaryShadowExpression<T>*   conclusion;
	};

	template <class T>
	FuzzyFactory<T>::FuzzyFactory(
		Not<T>* _not,
		And<T>* _and,
		Or<T>* _or,
		Then<T>* _then,
		Agg<T>* _agg,
		MamdaniDefuzz<T>* _defuzz
		)
	{
		not        = new UnaryShadowExpression<T>(_not);
		and        = new BinaryShadowExpression<T>(_and);
		or         = new BinaryShadowExpression<T>(_or);
		then       = new BinaryShadowExpression<T>(_then);
		agg        = new BinaryShadowExpression<T>(_agg);
		defuzz     = new BinaryShadowExpression<T>(_defuzz);
	}

	template <class T>
	FuzzyFactory<T>::FuzzyFactory(
		Not<T>* _not,
		And<T>* _and,
		Or<T>* _or,
		Then<T>* _then,
		Agg<T>* _agg,
		MamdaniDefuzz<T>* _defuzz,
		SugenoDefuzz<T>* _sugeno,
		SugenoConclusion<T>* _conclusion
		)
	{
		not        = new UnaryShadowExpression<T>(_not);
		and        = new BinaryShadowExpression<T>(_and);
		or         = new BinaryShadowExpression<T>(_or);
		then       = new BinaryShadowExpression<T>(_then);
		agg        = new BinaryShadowExpression<T>(_agg);
		defuzz     = new BinaryShadowExpression<T>(_defuzz);
		sugeno     = new NaryShadowExpression<T>(_sugeno);
		conclusion = new NaryShadowExpression<T>(_conclusion);
	}

	template <class T>
	FuzzyFactory<T>::~FuzzyFactory()
	{
		delete not;
		delete and;
		delete or;
		delete then;
		delete agg;
		delete defuzz;
		delete sugeno;
		delete conclusion;
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newNot(core::Expression<T>* o)
	{
		return newUnary(not, o);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newAnd(core::Expression<T>* l, core::Expression<T>* r)
	{
		return newBinary(and, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newOr(core::Expression<T>* l, core::Expression<T>* r)
	{
		return newBinary(or, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newThen(core::Expression<T>* l, core::Expression<T>* r)
	{
		return newBinary(then, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newAgg(core::Expression<T>* l, core::Expression<T>* r)
	{
		return newBinary(agg, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newDefuzz(core::Expression<T>* l, core::Expression<T>* r, const T& min, const T& max, const T& step)
	{
		MamdaniDefuzz<T>* target = (MamdaniDefuzz<T>*) defuzz->getTarget();	
		target->setMin(min);
		target->setMax(max);
		target->setStep(step);

		return newBinary(defuzz, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::newIs(Is<T>* s, core::Expression<T>* o)
	{
		return newUnary(s, o);
	}

	template <class T>
    core::Expression<T>* FuzzyFactory<T>::newSugeno(std::vector<core::Expression<T>*>* operands)
    {
        return newNary(sugeno, operands);
    }

    template <class T>
    core::Expression<T>* FuzzyFactory<T>::newNConclusion(std::vector<core::Expression<T>*>* operands)
    {
        return newNary(conclusion, operands);
    }

	template <class T>
	void FuzzyFactory<T>::changeNot(Not<T>* _not)
	{
		not->setTarget(_not);
	}

	template <class T>
	void FuzzyFactory<T>::changeAnd(And<T>* _and)
	{
		and->setTarget(_and);
	}

	template <class T>
	void changeOr(Or<T>* _or)
	{
		or->setTarget(_or);
	}

	template <class T>
	void FuzzyFactory<T>::changeThen(Then<T>* _then)
	{
		then->setTarget(_then);
	}

	template <class T>
	void FuzzyFactory<T>::changeAgg(Agg<T>* _agg)
	{
		agg->setTarget(_agg);
	}

	template <class T>
	void FuzzyFactory<T>::changeDefuzz(MamdaniDefuzz<T>* _defuzz)
	{
		defuzz->setTarget(_defuzz);
	}

	template <class T>
	void FuzzyFactory<T>::changeSugeno(SugenoDefuzz<T>* _sugeno)
	{
		sugeno->setTarget(_sugeno);
	}

	template <class T>
	void FuzzyFactory<T>::changeConclusion(SugenoConclusion<T>* _conclusion)
	{
		conclusion->setTarget(_conclusion);
	}
}

#endif
