#include "Pins/UserSlotPin.h"

#include "BeamEditorSettings.h"
#include "BeamCoreSettings.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "UserSlots/UserSlot.h"

void SUserSlotPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);	
}

TSharedRef<SWidget> SUserSlotPin::GetDefaultValueWidget()
{
	GetNames(AttributesList);

	// retrieve the previous value selected (or the first value as default)
	TSharedPtr<FName> InitialSelectedName = GetSelectedName();
	if (InitialSelectedName.IsValid())
	{
		SetPropertyWithName(*InitialSelectedName.Get());
	}

	if (GraphPinObj->LinkedTo.Num() > 0)
		return SGraphPin::GetDefaultValueWidget();

	return SAssignNew(NameComboBox, SNameComboBox) // you can display any widget here
        .ContentPadding(FMargin(6.0f, 2.0f)) // you can stylize how you want by the way, check Slate library
        .OptionsSource(&AttributesList) // this to create all possibilities
        .InitiallySelectedItem(InitialSelectedName) // the default or previous selected value
        .OnComboBoxOpening(this, &SUserSlotPin::OnComboBoxOpening) // this event is defined by the SNameComboBox
        .OnSelectionChanged(this, &SUserSlotPin::OnAttributeSelected); // dito
}

void SUserSlotPin::OnAttributeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		SetPropertyWithName(*ItemSelected);
	}
}

void SUserSlotPin::OnComboBoxOpening()
{
	TSharedPtr<FName> SelectedName = GetSelectedName();
	if (SelectedName.IsValid())
	{
		check(NameComboBox.IsValid());
		NameComboBox->SetSelectedItem(SelectedName);
	}
}

void SUserSlotPin::SetPropertyWithName(const FName& Name)
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FUserSlot::StaticStruct());

	// To set the property we need to use a FString
	// using this format: (MyPropertyName="My Value")
	// MyPropertyName is the property defined in our struct FSimpleNameAttribute
	FString PinString = TEXT("(Name=\"");
	PinString += *Name.ToString();
	PinString += TEXT("\")");

	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();

	if (CurrentDefaultValue != PinString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("Beamable", "ChangeUserSlotFromSettings", "Change UserSlot From Settings"));
		GraphPinObj->Modify();

		UE_LOG(LogTemp, Verbose, TEXT("Verify values old: \"%s\" chosen: \"%s\""), *CurrentDefaultValue, *PinString);

		if (PinString != GraphPinObj->GetDefaultAsString())
		{
			// Its important to use this function instead of GraphPinObj->DefaultValue
			// directly, cause it notifies the node from the pin is attached to.
			// So the node can listen this change and do things internally.
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, PinString);
			UE_LOG(LogTemp, Warning, TEXT("Setting Default: \"%s\" chosen: \"%s\""), *CurrentDefaultValue, *PinString);
		}
	}
}

TSharedPtr<FName> SUserSlotPin::GetSelectedName() const
{
	const int32 NameCount = AttributesList.Num();
	if (NameCount <= 0)
	{
		return NULL;
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

void SUserSlotPin::GetPropertyAsName(FName& OutName) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FUserSlot::StaticStruct());

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

EVisibility SUserSlotPin::GetDefaultValueVisibility() const
{
	if (GraphPinObj->LinkedTo.Num() > 0)
		return EVisibility::Collapsed;

	return SGraphPin::GetDefaultValueVisibility();
}

void SUserSlotPin::GetNames(TArray<TSharedPtr<FName>>& ShareableNames) const
{
	static const UBeamCoreSettings* BeamCoreRuntimeSettings = GetDefault<UBeamCoreSettings>();	
	const auto BP = FBlueprintEditorUtils::FindBlueprintForGraph(GraphPinObj->GetOwningNode()->GetGraph());
	if (BP && FBlueprintEditorUtils::IsEditorUtilityBlueprint(BP))
	{
		for (FString Name : BeamCoreRuntimeSettings->DeveloperUserSlots)
		{
			ShareableNames.Add(MakeShareable(new FName(Name)));
		}
	}
	else
	{
		for (FString Name : BeamCoreRuntimeSettings->RuntimeUserSlots)
		{
			ShareableNames.Add(MakeShareable(new FName(Name)));
		}
	}
}
