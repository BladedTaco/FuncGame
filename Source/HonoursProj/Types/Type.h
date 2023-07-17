// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Types/Types_gen.h"

#include "Type.generated.h"

inline const auto emptyPtrMap = TMap<UType*, UType*>();

// This class does not need to be modified.
UCLASS()
class HONOURSPROJ_API UType : public UObject
{
	GENERATED_BODY()
public:
	virtual EType GetType() const PURE_VIRTUAL(UType::GetType, return EType::ANY;);
	virtual TArray<UType*> GetTemplates() const PURE_VIRTUAL(UType::GetTemplates, return {}; );
	virtual TArray<UType*> GetTemplates(ETypeClass As) const;
	virtual TArray<UType*> GetTemplates(EType As) const;

	virtual UType* DeepCopy(const TMap<UType*, UType*>& ptrMap = emptyPtrMap) const PURE_VIRTUAL(UType::DeepCopy, return NULL; );

public:
	bool Supercedes(const UType* other) const;

	FString ToString() const;

	bool EqualTo(const UType* other) const;

	virtual bool UnifyWith(const UType* concreteType);

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
		bool Terminal() const;

	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypeConst* New(ETypeData InType, TArray<UType*> InTemplates);
	static UTypeConst* New(ETypeBase InType);
	virtual UType* DeepCopy(const TMap<UType*, UType*>& ptrMap = emptyPtrMap) const override;

	UFUNCTION(BlueprintCallable)
		static UTypeConst* MakeConst(const UType* InType);
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
		bool Valid() const;
	UFUNCTION(BlueprintCallable)
		UType* Get();

	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypePtr* New(UType* TypeVar, TArray<UType*> InTemplates);
	static UTypePtr* New(UType* TypeVar);

	virtual UType* DeepCopy(const TMap<UType*, UType*>& ptrMap = emptyPtrMap) const override;

	virtual bool UnifyWith(const UType* concreteType) override;
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
		bool ApplyEvidence(const UType* InType);
	UFUNCTION(BlueprintCallable)
		bool RemoveEvidence(const UType* InType);
	UFUNCTION(BlueprintCallable)
		void ResetEvidence();

	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypeVar* New(ETypeClass InType);
	virtual UType* DeepCopy(const TMap<UType*, UType*>& ptrMap = emptyPtrMap) const override;


	virtual bool UnifyWith(const UType* concreteType) override;
};
