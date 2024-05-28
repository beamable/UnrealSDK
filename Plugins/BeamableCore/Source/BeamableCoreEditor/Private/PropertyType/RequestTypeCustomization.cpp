#include "PropertyType/RequestTypeCustomization.h"

#include "DetailWidgetRow.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/RequestType.h"

#define LOCTEXT_NAMESPACE "RequestTypeCustomization"

TSharedRef<IPropertyTypeCustomization> FRequestTypeCustomization::MakeInstance()
{
	if (AttributesList.IsEmpty())
	{
		GetNames(AttributesList);
	}

	// Create the instance and returned a SharedRef
	return MakeShareable(new FRequestTypeCustomization());
}

void FRequestTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));
	// Get the property handler of the type property:
	const TSharedPtr<IPropertyHandle> NamePropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FRequestType, Name));
	check(NamePropertyHandle.IsValid());

	// retrieve its value as a text to display
	FText OutValue;
	NamePropertyHandle->GetValueAsDisplayText(OutValue);


	// then change the HeaderRow to add some Slate widget
	// clang-format off
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
		.ValueContent()[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(NameComboBox, SNameComboBox) // you can display any widget here
					.ContentPadding(FMargin(6.0f, 2.0f)) // you can stylize how you want by the way, check Slate library
					.OptionsSource(&AttributesList) // this to create all possibilities
					.InitiallySelectedItem(AttributesList[0]) // the default or previous selected value
					.OnComboBoxOpening(FOnComboBoxOpening::CreateLambda(
					                                       [this, NamePropertyHandle]()
					                                       {
						                                       if (NamePropertyHandle->IsValidHandle())
						                                       {
							                                       check(NameComboBox.IsValid());
							                                       FString Val;
							                                       NamePropertyHandle->GetValue(Val);
							                                       const auto SelectedName = AttributesList.FindByPredicate([NamePropertyHandle, Val](TSharedPtr<FName> n)
							                                       {
								                                       return n->ToString().Equals(Val);
							                                       });

							                                       NameComboBox->SetSelectedItem(*SelectedName);
						                                       }
					                                       })) // this event is defined by the SNameComboBox
					.OnSelectionChanged(SNameComboBox::FOnNameSelectionChanged::CreateLambda([this, NamePropertyHandle](TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
				                                       {
					                                       if (NamePropertyHandle->IsValidHandle())
					                                       {
						                                       NamePropertyHandle->SetValue(ItemSelected->ToString());
					                                       }
				                                       }))
			]
		];
}

void FRequestTypeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	// Should customize here soon
}

void FRequestTypeCustomization::GetNames(TArray<TSharedPtr<FName>>& ShareableNames)
{
	TArray<UClass*> RequestClasses;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->ImplementsInterface(UBeamBaseRequestInterface::StaticClass()))
			RequestClasses.Add(*It);
	}

	for (const auto& RequestClass : RequestClasses)
	{
		const auto Default = Cast<IBeamBaseRequestInterface>(RequestClass->GetDefaultObject());
		const auto ReqType = Default->GetRequestType();
		ShareableNames.Add(MakeShareable(new FName(ReqType.Name)));
	}
}
#undef LOCTEXT_NAMESPACE
