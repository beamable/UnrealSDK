#include "Pins/BeamContentIdPin.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"

void SBeamContentIdPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SBeamContentIdPin::GetDefaultValueWidget()
{
	Content = GEditor->GetEditorSubsystem<UBeamEditorContent>();
	GetContentOptions(ContentTypeNames, ContentTypeToIdsMap);

	// retrieve the previous value selected (or the first value as default)	
	const auto InitialSelectedId = GetSelectedId();
	if (InitialSelectedId.IsValid())
	{
		SetPropertyWithName(*InitialSelectedId.Get());
	}

	if (GraphPinObj->LinkedTo.Num() > 0)
		return SGraphPin::GetDefaultValueWidget();

	if(const auto InitialIds = GetIdsForSelectedType())
		Ids = TArray(*InitialIds);
	
	const auto InitialSelectedType = GetSelectedType();
	return SAssignNew(WidgetContainer, SVerticalBox) + SVerticalBox::Slot()
		[
			SAssignNew(TypeComboBox, SNameComboBox) // you can display any widget here
		.ContentPadding(FMargin(6.0f, 2.0f)) // you can stylize how you want by the way, check Slate library
		.OptionsSource(&ContentTypeNames) // this to create all possibilities
		.InitiallySelectedItem(InitialSelectedType) // the default or previous selected value
		.OnComboBoxOpening(this, &SBeamContentIdPin::OnTypeComboBoxOpening) // this event is defined by the SNameComboBox
		.OnSelectionChanged(this, &SBeamContentIdPin::OnTypeSelected) // dito
		]
		+ SVerticalBox::Slot()
		[
			SAssignNew(IdComboBox, SNameComboBox) // you can display any widget here
		.ContentPadding(FMargin(6.0f, 2.0f)) // you can stylize how you want by the way, check Slate library
		.OptionsSource(&Ids) // this to create all possibilities
		.InitiallySelectedItem(InitialSelectedId) // the default or previous selected value
		.OnComboBoxOpening(this, &SBeamContentIdPin::OnIdComboBoxOpening) // this event is defined by the SNameComboBox
		.OnSelectionChanged(this, &SBeamContentIdPin::OnIdSelected) // dito
		];
}

void SBeamContentIdPin::OnIdSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		SetPropertyWithName(*ItemSelected);
	}
}

void SBeamContentIdPin::OnTypeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (const auto NewIds = ContentTypeToIdsMap.Find(*ItemSelected); NewIds && (NewIds->Num() > 0))
		{
			SetPropertyWithName(*(*NewIds)[0]);
			this->Ids = TArray(*NewIds);
			IdComboBox->RefreshOptions();
			IdComboBox->SetSelectedItem(GetSelectedId());
		}
	}
}

void SBeamContentIdPin::OnTypeComboBoxOpening()
{
	TSharedPtr<FName> SelectedType = GetSelectedType();
	if (SelectedType.IsValid())
	{
		check(TypeComboBox.IsValid());
		TypeComboBox->SetSelectedItem(SelectedType);
	}
}

void SBeamContentIdPin::OnIdComboBoxOpening()
{
	TSharedPtr<FName> SelectedName = GetSelectedId();
	if (SelectedName.IsValid())
	{
		check(TypeComboBox.IsValid());
		IdComboBox->SetSelectedItem(SelectedName);
		Invalidate(EInvalidateWidgetReason::Layout);
	}
}

void SBeamContentIdPin::SetPropertyWithName(const FName& Name)
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FBeamContentId::StaticStruct());

	// To set the property we need to use a FString
	// using this format: (MyPropertyName="My Value")
	// MyPropertyName is the property defined in our struct FSimpleNameAttribute
	FString PinString = TEXT("(AsString=\"");
	PinString += *Name.ToString();
	PinString += TEXT("\")");

	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();

	if (CurrentDefaultValue != PinString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("Beamable", "ChangeContentId", "Change Content Id"));
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

TSharedPtr<FName> SBeamContentIdPin::GetSelectedId() const
{
	const int32 TypeCount = ContentTypeNames.Num();
	const int32 IdsCount = ContentTypeToIdsMap.Num();
	if (TypeCount <= 0 || IdsCount <= 0)
	{
		return NULL;
	}

	FName PropertyValue;
	GetPropertyAsName(PropertyValue);

	const FBeamContentId ContentId{PropertyValue.ToString()};
	FString TypeNameStr;
	if (Content->GetContentTypeFromId(ContentId, TypeNameStr))
	{
		const auto FoundIds = ContentTypeToIdsMap.Find(FName(TypeNameStr));
		if (!FoundIds || FoundIds->Num() == 0) return NULL;

		for (const auto& Name : *FoundIds)
		{
			if (Name->ToString().Equals(ContentId.AsString))
				return Name;
		}

		return (*FoundIds)[0];
	}

	return NULL;
}

TSharedPtr<FName> SBeamContentIdPin::GetSelectedType() const
{
	const int32 TypeCount = ContentTypeNames.Num();
	const int32 IdsCount = ContentTypeToIdsMap.Num();
	if (TypeCount <= 0 || IdsCount <= 0)
	{
		return NULL;
	}

	FName PropertyValue;
	GetPropertyAsName(PropertyValue);

	const FBeamContentId ContentId{PropertyValue.ToString()};

	FString TypeName;
	if (Content->GetContentTypeFromId(ContentId, TypeName))
	{
		for (const auto& Name : ContentTypeNames)
		{
			if (Name->ToString().Equals(TypeName))
				return Name;
		}

		return ContentTypeNames[0];
	}

	return NULL;
}

TArray<TSharedPtr<FName>>* SBeamContentIdPin::GetIdsForSelectedType() const
{
	TSharedPtr<FName> SelectedType = GetSelectedType();
	if (SelectedType.IsValid())
	{
		if (TArray<TSharedPtr<FName>>* Zxc = const_cast<TArray<TSharedPtr<FName>>*>(ContentTypeToIdsMap.Find(*SelectedType)))
		{
			return Zxc;
		}
	}

	return nullptr;
}

void SBeamContentIdPin::GetPropertyAsName(FName& OutName) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FBeamContentId::StaticStruct());

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

EVisibility SBeamContentIdPin::GetDefaultValueVisibility() const
{
	if (GraphPinObj->LinkedTo.Num() > 0)
		return EVisibility::Collapsed;

	return SGraphPin::GetDefaultValueVisibility();
}

void SBeamContentIdPin::GetContentOptions(TArray<TSharedPtr<FName>>& TypeNames, TMap<FName, TArray<TSharedPtr<FName>>>& PerTypeNameIds) const
{
	Content->GetContentTypeToIdMaps(PerTypeNameIds);
	TArray<FName> Names;
	PerTypeNameIds.GetKeys(Names);
	for (const auto& Name : Names)
	{
		TypeNames.Add(MakeShareable(new FName(Name)));
	}
}
