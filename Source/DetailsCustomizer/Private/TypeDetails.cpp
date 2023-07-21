#include "TypeDetails.h"

#include "Layout/Margin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Editor.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"

#include "Engine/RendererSettings.h"


#define LOCTEXT_NAMESPACE "FDetailsCustomizer"


TSharedRef<IDetailCustomization> FTypeDetails::MakeInstance() {
	// Create the instance and returned a SharedRef
	return MakeShareable(new FTypeDetails);
}

void FTypeDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) {
	UE_LOG(LogTemp, Warning, TEXT("Customizer"));

    // Create a category so this is displayed early in the properties
    IDetailCategoryBuilder& MyCategory = DetailBuilder.EditCategory(
        "CategoryName", 
        LOCTEXT("Extra info", "Row header name"),
        ECategoryPriority::Important
    );

    // You can get properties using the DetailBuilder:
    //MyProperty= DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(MyClass, MyClassPropertyName));

    MyCategory.AddCustomRow(LOCTEXT("Extra info", "Row header name"))
        .NameContent()
        [
            SNew(STextBlock)
            .Text(LOCTEXT("Extra info", "Custom row header name"))
        .Font(IDetailLayoutBuilder::GetDetailFont())
        ]
    .ValueContent().MinDesiredWidth(500)
        [
            SNew(STextBlock)
            .Text(LOCTEXT("Extra info", "Custom row content"))
        .Font(IDetailLayoutBuilder::GetDetailFont())
        ];
}


#undef LOCTEXT_NAMESPACE