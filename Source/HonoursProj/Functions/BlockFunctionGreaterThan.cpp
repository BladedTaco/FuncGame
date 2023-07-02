// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionGreaterThan.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Ord.h"
#include "Types/Int_gen.h"

#include "Types/Func_gen.h"

#include "MyUtils.h"



ABlockFunctionGreaterThan::ABlockFunctionGreaterThan() {
	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypeConst::New(ETypeData::NUMBER, { UTypePtr::New(F) })},
		{"B", UTypeConst::New(ETypeData::NUMBER, { UTypePtr::New(F) })},
	};
	Outputs = {
		{"A < B", UTypeConst::New(ETypeBase::BOOL)}
	};

}

Arr<ValArray&, TArray<void*>> ABlockFunctionGreaterThan::GetInnerFunc() {
	return Arr<ValArray&, TArray<void*>>([this](ValArray& values) -> TArray<void*> {

		// TODO: Make this reflect actual types
		//EType numType = this->TypeVars[0]->GetType();

		// Destruct Values
		const auto& [t0, t1] = Destruct<2, TArray, ValType>(values);
		const auto& [u0, v0] = t0;
		const auto& [u1, v1] = t1;

		// Get Number Type
		EType numType = u0->GetTemplates()[0]->GetType();

		// Do GT Calculation
		bool result;
		switch (numType) {
		case EType::INT:
			result = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
			break;
		case EType::FLOAT:
			result = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
			break;
		}


		this->TextComponent->SetText(FText::Format(FText::FromString(FString("GT {0}")), result));


		// Save Result and Return
		this->ConcreteOutputs = result;
		this->OutputValues = { ( void* )&this->ConcreteOutputs };
		return this->OutputValues;
	} );
}




//
//TArray<void*> ABlockFunctionGreaterThan::GetValue() {
//
//	ValArray inputs = CollectInputs();
//
//	EType numType = TypeVars[0]->GetType();
//
//	Arr<ValArray&, ValArray> impl = { [](ValArray& vals) -> ValArray {
//		bool result;
//		switch (numType) {
//		case EType::INT:
//			ConcreteOutputs = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//			break;
//		case EType::FLOAT:
//			ConcreteOutputs = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//			break;
//		}
//		OutputValues = { ( void* )&ConcreteOutputs };
//		return OutputValues;
//		return {};
//	} };
//
//	ApplyInputs({ inputs }, 0, &impl);
//
//	//const auto& [t0, v0] = inputs[0];
//	//const auto& [t1, v1] = inputs[1];
//
//	//// Fully Applied Function
//	//if (t0 && t1) {
//	//	bool result;
//	//	switch (numType) {
//	//	case EType::INT:
//	//		ConcreteOutputs = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//	//		break;
//	//	case EType::FLOAT:
//	//		ConcreteOutputs = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//	//		break;
//	//	}
//	//	OutputValues = { ( void* )&ConcreteOutputs };
//	//	return OutputValues;
//	//}
//
//
//
//	//auto f = curry([&](void* v0, void* v1) {
//	//	bool result;
//	//	switch (numType) {
//	//	case EType::INT:
//	//		ConcreteOutputs = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//	//		break;
//	//	case EType::FLOAT:
//	//		ConcreteOutputs = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//	//		break;
//	//	}
//	//	OutputValues = { ( void* )&ConcreteOutputs };
//	//	return OutputValues;
//	//});
//
//
//	using ValType = TTuple<UType*, void*>;
//
//	bool* outs = &ConcreteOutputs;
//	TArray<void*>* vals = &OutputValues;
//
//	auto flast = [=](ValType v0, ValType v1) {
//		const auto& [t0, v0] = v0;
//		const auto& [t1, v1] = inputs[1];
//		bool result;
//		switch (numType) {
//		case EType::INT:
//			*outs = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//			break;
//		case EType::FLOAT:
//			*outs = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//			break;
//		}
//		*vals = { ( void* )outs };
//		return *vals;
//	};
//
//
//
//
//
//
//
//	Function<void*, TArray<ValType>&, int, Arr<TArray<ValType>&, TArray<ValType>>*> ApplyInputs = \
//	[&ApplyInputs](TArray<ValType>& vals, int index, Arr<TArray<ValType>&,TArray<ValType>>* f) -> void* {
//		// Fully Applied Base Case
//		if (vals.Num() <= index) {
//			return &(*f)(vals);
//		}
//
//		// Extract type and value
//		const auto& [tn, vn] = vals[index];
//
//		// If no type for current Variable
//		if (!tn) {
//			return &[&](ValType val) {
//				vals[index] = val;
//				return ApplyInputs(vals, index, f);
//			};
//		// typed
//		} else {
//			return ApplyInputs(vals, index+1, f);
//		}
//	};
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	auto flast1 = [=](ValType v0, ValType v1) -> void* {
//		if (!v1) {
//			return &[=](ValType v1) -> void* {
//				return &flast(v0, v1);
//			};
//		} else {
//			return &flast(v0, v1);
//		}
//	};
//
//	auto flast2 = [=](ValType v0, ValType v1) -> void* {
//		if (!v0) {
//			return &[=](ValType v0) {
//				return flast1(v0, v1);
//			};
//		} else {
//			return flast1(v0, v1);
//		}
//	};
//
//	auto f = flast2(v0, v1);
//
//
//	//Arr<void*, void*> apply = { [=](void* in) -> void* { return f(in); } };
//
//	//// Partially applied function
//	//Arr<void*, void*> func = { [](void* in) { return in; } };
//
//	//if (t0) {
//	//	func = func(v0);
//	//} else {
//	//	func = { [=](void* v0) {return func(v0); } };
//	//}
//
//	void* out;
//	if (t0) {
//		if (t1) {
//
//		} else {
//			[](void* t1) {
//				
//			}
//		}
//	} else {
//
//	}
//
//
//
//	if (!t0 && !t1) {
//		// TODO: implement
//	} else if (!t0 || !t1) {
//		// TODO: implement
//	} else {
//
//	}
//	bool result;
//
//	void* res;
//
//	if (!t0 && !t1) {
//		switch (numType) {
//		case EType::INT:
//			res = ( void* )Ordinal<Number<int>>::gt<>;
//			break;
//		case EType::FLOAT:
//			res = ( void* )Ordinal<Number<float>>::gt<>;
//			break;
//		}
//	}
//
//
//	if (!!t0 || !!t1) {
//		switch (numType) {
//		case EType::INT:
//			result = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//			break;
//		case EType::FLOAT:
//			result = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//			break;
//		}
//	}
//
//	auto f = Ordinal<Number<int>>::gt<>;
//
//	bool result;
//	switch (numType) {
//	case EType::INT:
//		result = Ordinal<Number<int>>::gt<>(*(Number<int>*)v0)(*(Number<int>*)v1);
//		break;
//	case EType::FLOAT:
//		result = Ordinal<Number<float>>::gt<>(*(Number<float>*)v0)(*(Number<float>*)v1);
//		break;
//	}
//
//	OutputValues = { ( void* )&result };
//
//	return OutputValues;
//}