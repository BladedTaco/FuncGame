// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionFmap.h"
#include "Engine/World.h"


#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Functor.h"
#include "Types/Maybe_gen.h"
#include "Types/Func_gen.h"
#include "Types/Int_gen.h"

#include "MyUtils.h"

#include <any>


void ABlockFunctionFmap::SetFunctionTypes() {
	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::FUNCTOR);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"Func", UTypeConst::New(ETypeData::FUNC, { UTypePtr::New(A), UTypePtr::New(B) })},
		{"Over", UTypePtr::New(F, { UTypePtr::New(A) })}
	};
	Outputs = {
		{"Out",  UTypePtr::New(F, { UTypePtr::New(B) })}
	};
}




/*
SPECIALIZE TYPE


*/



//
//template <typename T>
//Arr<VStar, Arr<VStar, T>>* _h[2] = {
//	&Functor<Maybe<Number<int>>>::fmap<T>,
//	&Functor<Maybe<Number<float>>>::fmap<T>
//};
//
//
//
//
//template <typename T>
//Arr<void*, Arr<void*, T>> h[2] = {
//	Functor<Maybe<Number<int>>>::v_fmap<T>,
//	Functor<Maybe<Number<float>>>::v_fmap<T>
//};
//
//
//template <typename T>
//Arr<void*, Arr<void*, T>> g[10] = {
//	Functor<Maybe<Number<int>>>::v_fmap<T>,
//	Functor<Maybe<Number<float>>>::v_fmap<T>,
//	Functor< Maybe<Maybe<Number<int>>>>::v_fmap<T>,
//	Functor< Maybe<Maybe<Number<float>>>>::v_fmap<T>
//};
//
//
//template <typename T>
//Arr<void*, Arr<void*, T>> g[10] = {
//	Functor<Maybe<VStar>>::v_fmap<T>,
//	Functor<Arr<VStar, VStar>>::v_fmap<T>,
//
//	Functor<Maybe<Number<VStar>>>::v_fmap<T>,
//	Functor<Maybe<int>>::v_fmap<T>,
//	Functor<Maybe<Maybe<VStar>>>::v_fmap<T>,
//	Functor<Maybe<Arr<Maybe<VStar>, VStar>>>::v_fmap<T>,
//	Functor<Arr<Maybe<VStar>, VStar>>::v_fmap<T>,
//	Functor<Arr<Arr<VStar, VStar>, VStar>>::v_fmap<T>,
//};

//
//template <typename Return, template <typename...> class Typeclass, typename... Args>
//Return GetFunction(UType* type) {
//
//	auto x = Functor::_fmap(Arr<int, float>([](int x) {return 1.0f}), Maybe::Just(1));
//
//	switch (type->GetType()) {
//	case EType::MAYBE:
//		break;
//	case EType::INT:
//		return Typeclass<Maybe<Number<int>>>::Get("v_fmap")
//	}
//}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionFmap::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		return {};

		//auto& [t0, t1] = Destruct<2, TArray, VStar>(values);


		//auto x = Functor<Maybe<VStar>>::fmap<VStar>(t0)(t1);


		//Maybe<Number<int>> a = decltype(a)::Just({ 1 });
		//Arr<Number<int>, Number<int>> f = curry([](Number<int> a) { return a; });

		//auto x = Functor<decltype(a)>::fmap<decltype(f)::to>(f)(a);


		// TODO: Make this reflect actual types
		//EType numType = this->TypeVars[0]->GetType();

		//// Destruct Values
		//const auto& [t0, t1] = Destruct<2, TArray, ValType>(values);
		//const auto& [u0, v0] = t0;
		//const auto& [u1, v1] = t1;

		//TArray<UType*> templates = u1->GetTemplates();
		//const auto& [f1, f2] = Destruct<2, TArray, UType*>(templates);

		//EType fromType = f1->GetType();
		//EType toType = f2->GetType();

		//// Get Number Type
		//ETypeData wrapperType = ( ETypeData )u1->GetType();


		//auto f = Functor<Maybe<Number<int>>>::v_fmap<Number<float>>;
		//auto g = Functor<Maybe<Number<float>>>::v_fmap<Number<float>>;

		////h = &g;

		////h = &f;


		////auto y = f(v0)(v1);

		////Node<typename std::decay<decltype(*start)>::type>*

		//// Do GT Calculation
		//bool result;
		//switch (wrapperType) {
		//case ETypeData::FUNC:
		//	//Functor<Arr<void*, decltype(f1->GetType() == EType::INT ? rint : rfloat)>>::fmap<int>;
		//	break;
		//case ETypeData::MAYBE:
		//	//Functor<Maybe<int>>::fmap<int>;
		//	break;
		//}

		//this->TextComponent->SetText(FText::Format(FText::FromString(FString("GT {0}")), result));


		return {};

		//// Save Result and Return
		//this->ConcreteOutputs = result;
		//this->OutputValues = { ( void* )&this->ConcreteOutputs };
		//return this->OutputValues;
	} );
}
