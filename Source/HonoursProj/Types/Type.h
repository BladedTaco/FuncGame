// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Types_gen.h"
#include "HonoursProjGameInstance.h"

#include "Utils/ColourGroup.h"

#include "Type.generated.h"

class UTypeConst;

// This class does not need to be modified.
UCLASS()
class HONOURSPROJ_API UType : public UObject
{
	GENERATED_BODY()
public:
	virtual EType GetType() const PURE_VIRTUAL(UType::GetType, return EType::ANY;);
	virtual TArray<UType*> GetTemplates() const PURE_VIRTUAL(UType::GetTemplates, return {}; );
	virtual TArray<UType*> GetTemplates(ETypeClass As) const;
	virtual TArray<UType*> GetTemplates(ETypeData As) const;
	virtual TArray<UType*> GetTemplates(EType As) const;

	virtual UType* DeepCopy(TMap<UType*, UType*>& ptrMap) const PURE_VIRTUAL(UType::DeepCopy, return NULL; );

	UTypeConst* VolatileConst();

	virtual void ResetColour() PURE_VIRTUAL(UType::ResetColour, return; );

private:
	UType* RecursiveCopy();
public:
	UType();

	bool Supercedes(const UType* other) const;

	virtual FString ToString() const;

	UFUNCTION(BlueprintCallable, CallInEditor)
	FString UToString() const { return ToString(); }

	bool EqualTo(const UType* other) const;

	bool UnifyWith(UType* concreteType);
	virtual bool UnifyWith_Impl(UType* concreteType);


	virtual int GetColourIndex() const PURE_VIRTUAL(UType::GetColourIndex, return -1; );
	virtual TSharedPtr<int> ShareColour() const PURE_VIRTUAL(UType::ShareColour, return {}; );
	FColor GetColour() const;

protected:
	inline static UColourGroup* SharedColourGroup = NULL;

	UPROPERTY(EditAnywhere)
	UColourGroup* ColourGroup;

	UColourGroup* GetColourGroup() const;

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
		EType Type = EType::ANY;
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Templates = {};

	TSharedPtr<int> ColourPtr;
public:
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
		bool Terminal() const;

	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypeConst* New(ETypeData InType, TArray<UType*> InTemplates);
	static UTypeConst* New(ETypeBase InType);
	virtual UType* DeepCopy(TMap<UType*, UType*>& ptrMap) const override;

	virtual int GetColourIndex() const override;
	TSharedPtr<int> ShareColour() const override;

	virtual void ResetColour() override { GetColourGroup()->Split(GetColourIndex()); ColourPtr.Reset(); }


	UFUNCTION(BlueprintCallable)
		static UTypeConst* MakeConst(const UType* InType);
	UFUNCTION(BlueprintCallable)
		bool RestrictTo(UType* InType);
};

// A Class that relies entirely on a TypeVar for its Type Information
UCLASS()
class HONOURSPROJ_API UTypePtr : public UType {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Instanced)
		UType* Type = NULL;
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Templates = {};
	UPROPERTY(VisibleAnywhere)
		bool CopyTemplates = false;

public:
	UFUNCTION(BlueprintCallable)
		bool Valid() const;
	UFUNCTION(BlueprintCallable)
		UType* Get();

	virtual int GetColourIndex() const override;
	TSharedPtr<int> ShareColour() const override;
	virtual void ResetColour() override { Get()->ResetColour(); }


	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypePtr* New(UType* TypeVar, TArray<UType*> InTemplates);
	static UTypePtr* New(UType* TypeVar);

	virtual UType* DeepCopy(TMap<UType*, UType*>& ptrMap) const override;

	virtual bool UnifyWith_Impl(UType* concreteType) override;
};

// A Class That has an ETypeClass EType that gets resolved into an ETypeData or ETypeBase EType
UCLASS()
class HONOURSPROJ_API UTypeVar : public UType {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Instanced)
		TArray<UType*> Evidence = {};
	UPROPERTY(EditAnywhere)
		ETypeClass Type = ETypeClass::ANY;
	UPROPERTY(EditAnywhere, Instanced)
		UTypeConst* Instance = NULL;

	TSharedRef<int> ColourIndex = MakeShareable(new int(-1));

public:
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
		bool ApplyEvidence(UType* InType);
	UFUNCTION(BlueprintCallable)
		bool RemoveEvidence(const UType* InType);
	UFUNCTION(BlueprintCallable)
		void ReapplyEvidence();
	UFUNCTION(BlueprintCallable)
		void ResetEvidence();

	virtual int GetColourIndex() const override;
	TSharedPtr<int> ShareColour() const override;
	virtual void ResetColour() override { GetColourGroup()->Split(GetColourIndex()); if (IsValid(Instance)) { Instance->ResetColour(); } }



	virtual EType GetType() const override;
	virtual TArray<UType*> GetTemplates() const override;

	static UTypeVar* New(ETypeClass InType, bool bAssignColour = true);
	virtual UType* DeepCopy(TMap<UType*, UType*>& ptrMap) const override;

	virtual FString ToString() const override;

	virtual bool UnifyWith_Impl(UType* concreteType) override;
};
