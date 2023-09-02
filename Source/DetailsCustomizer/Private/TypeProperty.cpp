#include "TypeProperty.h"


#include "Layout/Margin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"

#include "IDetailChildrenBuilder.h"

#include "IDetailGroup.h"
#include "IDetailPropertyRow.h"


#include "IPropertyUtilities.h"

#include "Engine/RendererSettings.h"


#define LOCTEXT_NAMESPACE "FDetailsCustomizer"


struct Params {
	FString RetVal;
};

TSharedRef<IPropertyTypeCustomization> FTypeProperty::MakeInstance() {
	// Create the instance and returned a SharedRef
	return MakeShareable(new FTypeProperty());
}

void FTypeProperty::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
	class FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils) {

	auto SetName = [&]() {
		if (!StructPropertyHandle.Get().IsValidHandle()) return;
		if (auto prop = StructPropertyHandle->GetProperty()) {
			//TypeType = prop->GetCPPType();

			UObject* obj;
			StructPropertyHandle->GetValue(obj);


			if (obj && IsValid(obj)) {
				if (UFunction* f = obj->FindFunction("UToString")) {
					Params params = {};
					obj->ProcessEvent(f, &params);

					TypeName = params.RetVal;
					TypeType = obj->GetClass()->GetFName().ToString();

					//if (auto typ = Cast<UType>(obj)) {
					//	TypeName = typ->ToString();
					//	TypeType = typ->GetClass()->GetFName().ToString();
					//}
				}
			}
		}
	};

	SetName();
		
	StructPropertyHandle->SetOnChildPropertyValueChanged(FSimpleDelegate::CreateLambda(SetName));
		

	HeaderRow
		.NameContent()[
			StructPropertyHandle->CreatePropertyNameWidget(FText::GetEmpty(), FText::GetEmpty(), false)
		]
		.ValueContent()[


			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					
					SNew(STextBlock)
						.AutoWrapText(true)
						.Font(FEditorStyle::GetFontStyle("PropertyWindow.NormalFont"))
						.Text_Lambda([&]() {
						return FText::FromString(FString::Format(TEXT("{0} : {1}"), {TypeType, TypeName}));
					})

				]
			//StructPropertyHandle->CreatePropertyValueWidget()
		];

}

void FTypeProperty::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	class IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils) {


    uint32 NumChildren;
    StructPropertyHandle->GetNumChildren(NumChildren);


    for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex) {
        const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();

		uint32 NumChildren2;
		ChildHandle->GetNumChildren(NumChildren2);

		for (uint32 ChildIndex2 = 0; ChildIndex2 < NumChildren2; ++ChildIndex2) {
			auto childchild = ChildHandle->GetChildHandle(ChildIndex2).ToSharedRef();

			uint32 NumChildren3;
			childchild->GetNumChildren(NumChildren3);
			for (uint32 ChildIndex3 = 0; ChildIndex3 < NumChildren3; ++ChildIndex3) {

				auto child3 = childchild->GetChildHandle(ChildIndex3).ToSharedRef();
				
				TSharedRef<SWidget> nameWidget = child3->CreatePropertyNameWidget();
				TSharedRef<SWidget> valueWidget = child3->CreatePropertyValueWidget();

				auto& row = StructBuilder.AddProperty(child3);
				row.IsEnabled(true);

			}
		}
    }



}

#undef LOCTEXT_NAMESPACE