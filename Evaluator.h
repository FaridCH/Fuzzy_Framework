#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include "ValueModel.h"
#include "Expression.h"

namespace core
{
	template <class T>
	class Evaluator
	{
	public:
		typedef std::pair<std::vector<T>, std::vector<T>> Shape;

		Shape buildShape(const T&, const T&, const T&, core::ValueModel<T>*, core::Expression<T>*) const;
		std::ostream& printShape(const Shape&) const;
	};

	template <class T>
	typename Evaluator<T>::Shape Evaluator<T>::buildShape(const T& min, const T& max, const T& step, core::ValueModel<T>* v, core::Expression<T>* e) const
	{
		std::vector<T> x, y;
		T mem = v->evaluate();  // pour éviter les effets de bord

		for (T i = min; i <= max; i += step)
		{
			v->setValue(i);
			x.push_back(i);
			y.push_back(e->evaluate());
		}

		v->setValue(mem);  // pour éviter les effets de bord

		return Shape(x, y); // instanciation de la forme à partir de x et y
	}

	template <class T>
	typename std::ostream& Evaluator<T>::printShape(const Shape& s) const
	{
		std::ostream os;
		return os;
	}
}

#endif
