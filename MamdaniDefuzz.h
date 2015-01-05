#ifndef MAMDANIDEFUZZ_H
#define MAMDANIDEFUZZ_H

#include "BinaryExpression.h"
#include "Evaluator.h"
#include <vector>

using namespace core;

namespace fuzzy
{
	template <class T>
	class MamdaniDefuzz: public BinaryExpression<T>
	{
	public:
		typedef std::pair<std::vector<T>, std::vector<T>> Shape;

		MamdaniDefuzz():min(0), max(0), step(0) {};
		MamdaniDefuzz(const T& min, const T& max, const T& step): min(min), max(max), step(step) {};
		~MamdaniDefuzz() {};

		virtual void setMin(const T& _min)   { min = _min; }
		virtual void setMax(const T& _max)   { max = _max; }
		virtual void setStep(const T& _step) { step = _step; }

		virtual T evaluate(Expression<T>*, Expression<T>*) const;

	protected:
		virtual T defuzz(const Shape&) const = 0;

	private:
		T min, max, step;
	};

	template <class T>
	T MamdaniDefuzz<T>::evaluate(Expression<T>* l, Expression<T>* r) const
	{
		Evaluator<T> e;
		return defuzz(e.buildShape(min, max, step, (ValueModel<T>*) l, r));
	}
}

#endif