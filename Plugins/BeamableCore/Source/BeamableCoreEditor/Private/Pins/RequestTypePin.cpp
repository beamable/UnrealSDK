#include "Pins/RequestTypePin.h"

#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/RequestType.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"
#include "Kismet2/BlueprintEditorUtils.h"

void SRequestTypePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SRequestTypePin::GetDefaultValueWidget()
{
	GetNames(AttributesList);

	// retrieve the previous value selected (or the first value as default)
	const TSharedPtr<FName> InitialSelectedName = GetSelectedName();
	if (InitialSelectedName.IsValid())
	{
		SetPropertyWithName(*InitialSelectedName.Get());
	}

	return SAssignNew(NameComboBox, SNameComboBox) // you can display any widget here
        .ContentPadding(FMargin(6.0f, 2.0f)) // you can stylize how you want by the way, check Slate library
        .OptionsSource(&AttributesList) // this to create all possibilities
        .InitiallySelectedItem(InitialSelectedName) // the default or previous selected value
        .OnComboBoxOpening(this, &SRequestTypePin::OnComboBoxOpening) // this event is defined by the SNameComboBox
        .OnSelectionChanged(this, &SRequestTypePin::OnAttributeSelected); // dito
}

void SRequestTypePin::OnAttributeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo) const
{
	if (ItemSelected.IsValid())
	{
		SetPropertyWithName(*ItemSelected);
	}
}

void SRequestTypePin::OnComboBoxOpening() const
{
	const TSharedPtr<FName> SelectedName = GetSelectedName();
	if (SelectedName.IsValid())
	{
		check(NameComboBox.IsValid());
		NameComboBox->SetSelectedItem(SelectedName);
	}
}

void SRequestTypePin::SetPropertyWithName(const FName& Name) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FRequestType::StaticStruct());

	// To set the property we need to use a FString
	// using this format: (MyPropertyName="My Value")
	// MyPropertyName is the property defined in our struct FSimpleNameAttribute
	FString PinString = TEXT("(Name=\"");
	PinString += *Name.ToString();
	PinString += TEXT("\")");

	const FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();

	if (CurrentDefaultValue != PinString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("Beamable", "ChangeRequestType", "Change RequestType"));
		GraphPinObj->Modify();

		UE_LOG(LogTemp, Verbose, TEXT("Verify values old: \"%s\" chosen: \"%s\""), *CurrentDefaultValue, *PinString);

		if (PinString != GraphPinObj->GetDefaultAsString())
		{
			// Its important to use this function instead of GraphPinObj->DefaultValue
			// directly, cause it notifies the node from the pin is attached to.
			// So the node can listen this change and do things internally.
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, PinString);
		}
	}
}

TSharedPtr<FName> SRequestTypePin::GetSelectedName() const
{
	const int32 NameCount = AttributesList.Num();
	if (NameCount <= 0)
	{
		return nullptr;
	}

	FName Name;
	GetPropertyAsName(Name);

	for (int32 NameIndex = 0; NameIndex < NameCount; ++NameIndex)
	{
		if (Name == *AttributesList[NameIndex].Get())
		{
			return AttributesList[NameIndex];
		}
	}
	// no value has been found, return a default value
	return AttributesList[0];
}

void SRequestTypePin::GetPropertyAsName(FName& OutName) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FRequestType::StaticStruct());

	// As we saw in the SListNameFromConfigPin::SetPropertyWithName()
	// The value is saved in the format (MyPropertyName="My Value") as a FString.
	// So we have to retrieve the real value and convert it to a FName
	FString PinString = GraphPinObj->GetDefaultAsString();

	if (PinString.StartsWith(TEXT("(")) && PinString.EndsWith(TEXT(")")))
	{
		PinString = PinString.LeftChop(1);
		PinString = PinString.RightChop(1);
		PinString.Split("=", NULL, &PinString);

		if (PinString.StartsWith(TEXT("\"")) && PinString.EndsWith(TEXT("\"")))
		{
			PinString = PinString.LeftChop(1);
			PinString = PinString.RightChop(1);
		}
	}

	if (!PinString.IsEmpty())
	{
		OutName = *PinString;
	}
}

void SRequestTypePin::GetNames(TArray<TSharedPtr<FName>>& ShareableNames) const
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
