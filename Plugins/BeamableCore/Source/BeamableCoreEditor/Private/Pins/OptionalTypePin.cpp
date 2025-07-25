#include "Pins/OptionalTypePin.h"

#include "BeamEditorSettings.h"
#include "BeamCoreSettings.h"
#include "BeamK2.h"
#include "GraphEditorSettings.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "UserSlots/UserSlot.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

void SOptionalTypePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SOptionalTypePin::GetDefaultValueWidget()
{
	// if (GraphPinObj->LinkedTo.Num() > 0)
		return SGraphPin::GetDefaultValueWidget();

	// TODO: Discuss with Epic regarding the best way of making Optional Pins with Default based on whether its a bool/number+string/enum 
	// const auto OptionalType = GetOptionalType();
	// const auto bIsTextBasedDefault = CanProvideTextBoxDefaultTypes.Contains(OptionalType);
	// const auto bIsComboBoxDefault = OptionalType.StartsWith("E"); // If it's an enum optional
	//
	// // If we don't support in-pin default editing widgets, just return the original one.
	// if (!bIsTextBasedDefault && !bIsComboBoxDefault)
	// 	return SGraphPin::GetDefaultValueWidget();
	//
	// // Otherwise, make a checkbox inside a horizontal box.
	// SAssignNew(HorizontalBox, SHorizontalBox) + SHorizontalBox::Slot()
	//                                             .AutoWidth()
	//                                             .MaxWidth(40)
	//                                             .HAlign(HAlign_Left)
	// [
	// 	SAssignNew(OptionalCheckBox, SCheckBox).OnCheckStateChanged(this, &SOptionalTypePin::OnCheckboxChanged)
	// ];
	//
	//
	// // If it's text box based, let's create the text-box
	// if (CanProvideTextBoxDefaultTypes.Contains(OptionalType))
	// {
	// 	HorizontalBox->AddSlot()
	// 	             .AutoWidth()
	// 	             .MaxWidth(256)
	// 	             .Padding(2, 0)
	// 	             .HAlign(HAlign_Left)[
	// 		SNew(SMultiLineEditableTextBox)
	// 		.AllowMultiLine(true)
	// 		.OnTextChanged(this, &SOptionalTypePin::OnTextDefaultChanged)
	// 	];
	// }
	//
	// // If it's enum-based, let's make a dropdown with the enum names 
	// if (OptionalType.StartsWith("E"))
	// {
	// 	OptionalEnumType = FindObject<UEnum>(ANY_PACKAGE, *OptionalType, true);	
	//
	// 	TArray<TSharedPtr<int32>> ComboItems;
	// 	for (int32 EnumIndex = 0; EnumIndex < OptionalEnumType->NumEnums() - 1; ++EnumIndex)
	// 	{
	// 		// Ignore hidden enum values
	// 		if (!OptionalEnumType->HasMetaData(TEXT("Hidden"), EnumIndex))
	// 		{
	// 			TSharedPtr<int32> EnumIdxPtr(new int32(EnumIndex));
	// 			ComboItems.Add(EnumIdxPtr);
	// 		}
	// 	}
	//
	// 	HorizontalBox->AddSlot()
	// 	             .AutoWidth()
	// 	             .MaxWidth(256)
	// 	             .Padding(2, 0)
	// 	             .HAlign(HAlign_Left)[
	// 		SAssignNew(EnumValuesComboBox, SPinComboBox)
	// 		.ComboItemList(ComboItems)
	// 		.OnSelectionChanged(this, &SOptionalTypePin::OnComboBoxSelectionChanged)
	// 	];
	// }
	//
	// return HorizontalBox.ToSharedRef();
}


FString SOptionalTypePin::GetOptionalType()
{
	const auto PinType = GraphPinObj->PinType;

	const auto OptionalStruct = Cast<UScriptStruct>(PinType.PinSubCategoryObject);
	ensureAlways(OptionalStruct);

	return OptionalStruct->GetMetaData(BeamK2::MD_BeamOptionalType);
}

FString SOptionalTypePin::BuildDefaultValueString()
{
	FString Val = TEXT("(");
	Val += TEXT("IsSet=");
	Val += OptionalCheckBox->IsChecked() ? TEXT("true") : TEXT("false");
	Val += ",";
	Val += TEXT("Val=\"");
	Val += OptionalDefaultValue;
	Val += "\"";
	Val += TEXT(")");
	return Val;
}

void SOptionalTypePin::OnCheckboxChanged(ECheckBoxState CheckBoxState)
{
	const auto OptionalType = GetOptionalType();
	// If we are of a type that allows a default, let's have a default enabled.
	if (OptionalType.Equals(TEXT("FString")))
	{
		const auto NewDefault = BuildDefaultValueString();
		GraphPinObj->GetSchema()->TrySetDefaultText(*GraphPinObj, FText::FromString(NewDefault));
		UE_LOG(LogTemp, Warning, TEXT("Toggling checkbox of string optional type %c. %s"), TCHAR(CheckBoxState), *GraphPinObj->GetDefaultAsString());
	}
}

void SOptionalTypePin::OnTextDefaultChanged(const FText& Text)
{
	const auto OptionalType = GetOptionalType();
	// If we are of a type that allows a default, let's have a default enabled.
	if (OptionalType.Equals(TEXT("FString")))
	{
		OptionalDefaultValue = Text.ToString();
		const auto NewDefault = BuildDefaultValueString();
		GraphPinObj->GetSchema()->TrySetDefaultText(*GraphPinObj, FText::FromString(NewDefault));
		UE_LOG(LogTemp, Warning, TEXT("Changing Default text of optional string %s"), *Text.ToString());
	}
}


void SOptionalTypePin::OnComboBoxSelectionChanged(TSharedPtr<int32> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		check(OptionalEnumType)

		FString EnumSelectionString;
		if (ItemSelected.IsValid())
		{
			check(*ItemSelected < OptionalEnumType->NumEnums() - 1);
			EnumSelectionString = OptionalEnumType->GetNameStringByIndex(*ItemSelected);
		}
		else
		{
			EnumSelectionString = FName(NAME_None).ToString();
		}


		if (GraphPinObj->GetDefaultAsString() != EnumSelectionString)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeEnumPinValue", "Change Enum Pin Value"));
			GraphPinObj->Modify();

			//Set new selection
			OptionalDefaultValue = EnumSelectionString;
			const auto NewDefault = BuildDefaultValueString();
			GraphPinObj->GetSchema()->TrySetDefaultText(*GraphPinObj, FText::FromString(NewDefault));
		}
	}
}

FSlateColor SOptionalTypePin::GetPinColor() const
{
	if (!GraphPinObj) return SGraphPin::GetPinColor();

	const auto PinType = GraphPinObj->PinType;
	const auto Settings = GetDefault<UGraphEditorSettings>();
	const auto PinColors = GetDefault<UBeamEditorSettings>()->OptionalTypePinColors;

	if (const auto OptionalStruct = Cast<UScriptStruct>(PinType.PinSubCategoryObject))
	{
		const auto OptionalType = OptionalStruct->GetMetaData(BeamK2::MD_BeamOptionalType);

		if (OptionalType.Equals(UnrealStringType))
			return Settings->StringPinTypeColor;

		if (OptionalType.Equals(UnrealBoolType))
			return Settings->BooleanPinTypeColor;

		if (OptionalType.Equals(UnrealByteType))
			return Settings->BytePinTypeColor;

		if (OptionalType.Equals(UnrealIntType))
			return Settings->IntPinTypeColor;

		if (OptionalType.Equals(UnrealInt64Type))
			return Settings->Int64PinTypeColor;

		// Enums are defined as byte colors
		if (OptionalType.StartsWith("E"))
			return Settings->BytePinTypeColor;

		if (PinColors.Contains(OptionalType))
			return PinColors.FindRef(OptionalType);
	}

	return Settings->StructPinTypeColor;
}


EVisibility SOptionalTypePin::GetDefaultValueVisibility() const
{
	if (GraphPinObj->LinkedTo.Num() > 0)
		return EVisibility::Collapsed;

	return SGraphPin::GetDefaultValueVisibility();
}