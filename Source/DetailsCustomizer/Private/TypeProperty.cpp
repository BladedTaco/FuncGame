#include "TypeProperty.h"


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

#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"

#include "Engine/RendererSettings.h"


#define LOCTEXT_NAMESPACE "FDetailsCustomizer"

TSharedRef<IPropertyTypeCustomization> FTypeProperty::MakeInstance() {
	// Create the instance and returned a SharedRef
	return MakeShareable(new FTypeProperty());
}

void FTypeProperty::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
	class FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils) {
	UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));
	// Should customize here soon

  /*  uint32 NumChildren;
    StructPropertyHandle->GetNumChildren(NumChildren);

    for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex) {
        const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();

        
        ChildHandle->GetProperty()
    }*/

    HeaderRow
        .NameContent()
        [
            StructPropertyHandle->CreatePropertyNameWidget(LOCTEXT("Prop Name", "New property header name"))
        ]
    .ValueContent().MinDesiredWidth(500)
        [
            SNew(STextBlock)
            .Text(LOCTEXT("Extra info", "Some new representation"))
        .Font(IDetailLayoutBuilder::GetDetailFont())
        ];
    

    //HeaderRow.NameContent()[
    //    StructPropertyHandle->CreatePropertyNameWidget(
    //        LOCTEXT("Property header", "New property header name")
    //    )
    //];

    //HeaderRow
    //    .NameContent()
    //    [
    //        StructPropertyHandle->CreatePropertyNameWidget(
    //            LOCTEXT("Property header", "New property header name")
    //        )
    //    ]
    //.ValueContent().MinDesiredWidth(500)
    //    [
    //        SNew(STextBlock)
    //        .Text(LOCTEXT("Extra info", "Some new representation"))
    //    .Font(IDetailLayoutBuilder::GetDetailFont())
    //    ];


}

void FTypeProperty::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	class IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils) {


    uint32 NumChildren;
    StructPropertyHandle->GetNumChildren(NumChildren);

    for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex) {
        const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();
        
        StructBuilder.AddProperty(ChildHandle);
    }







	// Should customize here soon

    //TSharedPtr<IPropertyHandle> TypePropertyHandle = StructPropertyHandle->GetChildHandle(
    //    GET_MEMBER_NAME_CHECKED(FMyStruct, Type)
    //);


    //TSharedPtr<IPropertyUtilities> PropertyUtils = StructCustomizationUtils.GetPropertyUtilities();
    //uint32 NumberOfChild;
    //if (StructPropertyHandle->GetNumChildren(NumberOfChild) == FPropertyAccess::Success) {
    //    for (uint32 Index = 0; Index < NumberOfChild; ++Index) {
    //        TSharedRef<IPropertyHandle> ChildPropertyHandle = StructPropertyHandle->GetChildHandle(Index).ToSharedRef();
    //        StructBuilder.AddProperty(ChildPropertyHandle);
    //    }
    //}
    //
   
    //
    //
    //
    //

    //StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
    //    .NameContent()
    //    [
    //        SNew(STextBlock)
    //        .Text(LOCTEXT("Extra info", "Custom row header name"))
    //    .Font(IDetailLayoutBuilder::GetDetailFont())
    //    ]
    //.ValueContent().MinDesiredWidth(500)
    //    [
    //        SNew(STextBlock)
    //        .Text(LOCTEXT("Extra info", "Custom row content"))
    //    .Font(IDetailLayoutBuilder::GetDetailFont())
    //    ];
}

#undef LOCTEXT_NAMESPACE