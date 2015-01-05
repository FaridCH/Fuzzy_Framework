#include "stdafx.h"

#include "NullExpressionException.h"
#include "AndMin.h"
#include "AndMult.h"
#include "OrMax.h"
#include "OrPlus.h"
#include "IsTriangle.h"
#include "NotMinus1.h"
#include "ThenMin.h"
#include "ValueModel.h"
#include "CogDefuzz.h"
#include "AggPlus.h"
#include "AggMax.h"
#include "SugenoThen.h"
#include "SugenoDefuzz.h"
#include "SugenoConclusion.h"

#include "FuzzyFactory.h"

#include <iostream>

using namespace core;
using namespace fuzzy;

void testAndMin()
{
	AndMin<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMin(" << v1->evaluate() << ", " << v2->evaluate() << "): " << op.evaluate(v1, v2) << std::endl;
}

void testAndMult()
{
	AndMult<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMult(" << v1->evaluate() << ", " << v2->evaluate() << "): " << op.evaluate(v1, v2) << std::endl;
}

void testOrMax()
{
	OrMax<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "OrMax(" << v1->evaluate() << ", " << v2->evaluate() << "): " << op.evaluate(v1, v2) << std::endl;
}

void testOrPlus()
{
	OrPlus<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMult(" << v1->evaluate() << ", " << v2->evaluate() << "): " << op.evaluate(v1, v2) << std::endl;
}

void testIsTriangle()
{
	IsTriangle<float> op(0.2f, 0.4f, 0.7f);
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "IsTriangle(" << v1->evaluate() << "): " << op.evaluate(v1) << std::endl;
	std::cout << "IsTriangle(" << v2->evaluate() << "): " << op.evaluate(v2) << std::endl;
}

void testDuCours()
{
	//operators
	NotMinus1<float>        opNot;
	AndMin<float>           opAnd;
	OrMax<float>            opOr;
	ThenMin<float>          opThen;
	AggPlus<float>          opAgg;
	CogDefuzz<float>        opDefuzz;
	SugenoDefuzz<float>     opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	//service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	//tips
	IsTriangle<float> cheap(0,5,10);
	IsTriangle<float> average(10,15,20);
	IsTriangle<float> generous(20,25,30);

	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);
	ValueModel<float> tips(0);

	Expression<float> *r =
		f.newAgg(
			f.newAgg(	
				f.newThen(
					f.newIs(&poor, &service),
					f.newIs(&cheap, &tips)
				),
				f.newThen(
					f.newIs(&good, &service),
					f.newIs(&average, &tips)
				)
			),
			f.newThen(
				f.newIs(&excellent, &service),
				f.newIs(&generous, &tips)
			)
		);

	//defuzzification
	Expression<float> *system = f.newDefuzz(&tips, r, 0, 30, 1);

	//apply input
	float s;
	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.setValue(s);
		std::cout << "tips -> " << system->evaluate() << std::endl;
	}
}

void testMamdani()
{
	//operators
	NotMinus1<float>        opNot;
	AndMin<float>           opAnd;
	OrMax<float>            opOr;
	ThenMin<float>          opThen;
	AggPlus<float>          opAgg;
	CogDefuzz<float>        opDefuzz;

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz);

	//membership function
	//service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	//food
	IsTriangle<float> rancid(-5,0,5);
	IsTriangle<float> delicious(5,10,15);
	//tips
	IsTriangle<float> cheap(0,5,10);
	IsTriangle<float> average(10,15,20);
	IsTriangle<float> generous(20,25,30);

	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);
	ValueModel<float> tips(0);

	Expression<float> *r =
		f.newAgg(
			f.newAgg(
				f.newThen(
					f.newOr(
						f.newIs(&poor, &service),
						f.newIs(&rancid, &food)
					),
					f.newIs(&cheap, &tips)
				),
				f.newThen(
					f.newIs(&good, &service),
					f.newIs(&average, &tips)
				)
			),
			f.newThen(
				f.newOr(
					f.newIs(&excellent, &service),
					f.newIs(&delicious, &food)
				),
				f.newIs(&generous, &tips)
			)
		);

	//defuzzification
	Expression<float> *system = f.newDefuzz(&tips, r, 0, 25, 1); // 25=max, 0=min, 1=step

	//apply input
	float s, fo;

	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.setValue(s);
		std::cout << "food : ";
		std::cin >> fo;
		food.setValue(fo);
		std::cout << "tips -> " << system->evaluate() << std::endl;
	}
}

void testSugenoDefuzz()
{
	//operators
	NotMinus1<float>    opNot;
	AndMin<float>       opAnd;
	OrMax<float>        opOr;
	SugenoThen<float>   opThen;
	AggMax<float>       opAgg;
	CogDefuzz<float>    opDefuzz;
	SugenoDefuzz<float> opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	// service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	// food
	IsTriangle<float> rancid(-5,0,5);
	IsTriangle<float> delicious(5,10,15);
	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);

	//output : ces variables vont stocker le résultat de SugenoConclusion (zi)
	std::vector<Expression<float>*> SC_service_food;
	SC_service_food.push_back(&service);
	SC_service_food.push_back(&food);

	std::vector<Expression<float>*> SC_service;
	SC_service.push_back(&service);

	//rules
	Expression<float> *r =
		f.newThen(
			f.newOr(
				f.newIs(&poor, &service),
				f.newIs(&rancid, &food)
			),
			f.newNConclusion(&SC_service_food)
		);

	Expression<float> *r1 =
		f.newThen(
			f.newIs(&good, &service),
			f.newNConclusion(&SC_service)
		);

	Expression<float> *r2 =
		f.newThen(
			f.newOr(
				f.newIs(&excellent, &service),
				f.newIs(&delicious, &food)
			),
			f.newNConclusion(&SC_service_food)
		);

	std::vector<Expression<float>*> operands;
	operands.push_back(r);
	operands.push_back(r1);
	operands.push_back(r2);

	//defuzzification
	Expression<float> *system = f.newSugeno(&operands);

	//apply input
	float s, foo;
	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.setValue(s);
		std::cout << "food : ";
		std::cin >> foo;
		food.setValue(foo);
		std::cout << "tips -> " << system->evaluate() << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//testAndMin();
	//testAndMult();
	//testOrMax();
	//testOrPlus();
	//testIsTriangle();

	//testMamdani();
	testDuCours();
	//testSugenoDefuzz();

	return 0;
}

