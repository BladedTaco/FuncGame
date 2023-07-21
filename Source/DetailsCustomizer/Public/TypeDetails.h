#pragma once

#include "CoreMinimal.h"

#include "IDetailCustomization.h"


class DETAILSCUSTOMIZER_API FTypeDetails : public IDetailCustomization
{
public:
	/**
	 * It is just a convenient helpers which will be used
	 * to register our customization. When the propertyEditor module
	 * find our FMyStruct property, it will use this static method
	 * to instanciate our customization object.
	 */
	static TSharedRef<IDetailCustomization> MakeInstance();

	// BEGIN IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	// END IDetailCustomization interface
};