#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "EditorUserWidget.generated.h"


/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class HONOURSPROJ_API UEditorUserWidget : public UUserWidget {
	GENERATED_BODY()
public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
};
