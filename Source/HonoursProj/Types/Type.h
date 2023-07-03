// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Types/Types_gen.h"

#include "Type.generated.h"

// This class does not need to be modified.
UCLASS()
class HONOURSPROJ_API UType : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		virtual EType GetType() PURE_VIRTUAL(UType::GetType, return EType::ANY;);
	UFUNCTION(BlueprintCallable)
		virtual TArray<UType*> GetTemplates() PURE_VIRTUAL(UType::GetTemplates, return {}; );
	UFUNCTION(BlueprintCallable)
		virtual UType* DeepCopy() PURE_VIRTUAL(UType::DeepCopy, return NULL; );

public:
	UFUNCTION()
		bool Supercedes(UType* other);

	//~UType() {
	//	UE_LOG(LogTemp, Warning, TEXT("Type Destroyed"));
	//}
	//UType() {
	//	UE_LOG(LogTemp, Warning, TEXT("Type Created"));
	//}
};


// A Class That has an ETypeBase or ETypeData EType
UCLASS()
class HONOURSPROJ_API UTypeConst : public UType {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		EType Type;
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Templates;

public:
	UFUNCTION(BlueprintCallable)
		bool Terminal();

	virtual EType GetType() override;
	virtual TArray<UType*> GetTemplates() override;

	static UTypeConst* New(ETypeData InType, TArray<UType*> InTemplates);
	static UTypeConst* New(ETypeBase InType);
	virtual UType* DeepCopy() override;

	UFUNCTION(BlueprintCallable)
		static UTypeConst* MakeConst(UType* InType);
	UFUNCTION(BlueprintCallable)
		void RestrictTo(UType* InType);
};

// A Class that relies entirely on a TypeVar for its Type Information
UCLASS()
class HONOURSPROJ_API UTypePtr : public UType {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Instanced)
		UType* Type;
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Templates;
	UPROPERTY(VisibleAnywhere)
		bool CopyTemplates;

public:
	UFUNCTION(BlueprintCallable)
		bool Valid();
	UFUNCTION(BlueprintCallable)
		UType* Get();

	virtual EType GetType() override;
	virtual TArray<UType*> GetTemplates() override;

	static UTypePtr* New(UType* TypeVar, TArray<UType*> InTemplates);
	static UTypePtr* New(UType* TypeVar);

	virtual UType* DeepCopy() override;
};

// A Class That has an ETypeClass EType that gets resolved into an ETypeData or ETypeBase EType
UCLASS()
class HONOURSPROJ_API UTypeVar : public UType {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Evidence;
	UPROPERTY(EditAnywhere)
		ETypeClass Type;
	UPROPERTY(EditAnywhere, Instanced)
		UTypeConst* Instance;

public:
	UFUNCTION(BlueprintCallable)
		bool ApplyEvidence(UType* InType);
	UFUNCTION(BlueprintCallable)
		bool RemoveEvidence(UType* InType);

	virtual EType GetType() override;
	virtual TArray<UType*> GetTemplates() override;

	static UTypeVar* New(ETypeClass InType);
	virtual UType* DeepCopy() override;
};
