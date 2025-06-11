#include "PropertyType/BeamContentIdCustomization.h"

#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "BeamContentIdCustomization"

UBeamEditorContent* FBeamContentIdCustomization::Content;
TArray<TSharedPtr<FName>> FBeamContentIdCustomization::ContentTypeNames;
TMap<FName, TArray<TSharedPtr<FName>>> FBeamContentIdCustomization::ContentTypeToIdsMap;

TSharedRef<IPropertyTypeCustomization> FBeamContentIdCustomization::MakeInstance()
{
	Content = GEditor->GetEditorSubsystem<UBeamEditorContent>();
	GetContentOptions(ContentTypeNames, ContentTypeToIdsMap);

	// Create the instance and returned a SharedRef
	return MakeShareable(new FBeamContentIdCustomization());
}

void FBeamContentIdCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                  FDetailWidgetRow& HeaderRow,
                                                  IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));
	// Get the property handler of the type property:
	TSharedPtr<IPropertyHandle> AsStringPropertyHandle;
	HasTypeFilter = false;
	OnlyExplicitTypes = false;
	if (const auto StructProp = CastField<FStructProperty>(StructPropertyHandle->GetProperty()))
	{		
		if (StructPropertyHandle->HasMetaData("BeamContentTypeFilterMode"))
		{
			const auto FilterMode = StructPropertyHandle->GetMetaData("BeamContentTypeFilterMode");
			OnlyExplicitTypes = FilterMode.Equals(FString("root"));
		}
		if (StructPropertyHandle->HasMetaData("BeamContentTypeFilter"))
		{
			TArray<FString> BeamContentTypeFilterArray;
			HasTypeFilter = true;
			const auto BeamContentTypeFilter = StructPropertyHandle->GetMetaData("BeamContentTypeFilter");
			BeamContentTypeFilter.ParseIntoArray(BeamContentTypeFilterArray, TEXT(","));
			TArray<FName> TypesToRemove;
			TMap<FString, FArrayOfString> OutMappings;
			Content->FindSubTypesOfContentType(BeamContentTypeFilterArray,OutMappings);

			for (const auto& Map : ContentTypeToIdsMap)
			{
				const auto ExampleContent = Map.Value[0].Get()->ToString();
				const auto TypeId = FBeamContentId(ExampleContent).GetTypeId();
				bool GoodContent = false;
				for(const auto& TT : OutMappings)
				{
					for(const auto& El: TT.Value.Values)
					{
						if (!OnlyExplicitTypes && TypeId.StartsWith(El))
						{
							GoodContent = true;
							break;
						}
						if(OnlyExplicitTypes && TypeId.Equals(El))
						{
							GoodContent = true;
							break;
						}
					}
				}
				if (!GoodContent)
				{
					TypesToRemove.Add(Map.Key);
				}
			}
			for (const auto& Rem : TypesToRemove)
			{
				ContentTypeToIdsMap.Remove(Rem);
			}
		}
		if (StructProp->Struct == FBeamContentId::StaticStruct())
			AsStringPropertyHandle = StructPropertyHandle->GetChildHandle(
				GET_MEMBER_NAME_CHECKED(FBeamContentId, AsString));

		if (StructProp->Struct == FBeamContentLink::StaticStruct())
			AsStringPropertyHandle = StructPropertyHandle->GetChildHandle(
				GET_MEMBER_NAME_CHECKED(FBeamContentLink, AsString));
	}

	check(AsStringPropertyHandle.IsValid());


	const auto TypeComboBoxOpenHandler = FOnComboBoxOpening::CreateRaw(
		this, &FBeamContentIdCustomization::OnTypeComboBoxOpening, AsStringPropertyHandle);
	const auto TypeComboBoxSelectHandler = SNameComboBox::FOnNameSelectionChanged::CreateRaw(
		this, &FBeamContentIdCustomization::OnTypeSelected, AsStringPropertyHandle);

	const auto IdsComboBoxOpenHandler = FOnComboBoxOpening::CreateRaw(
		this, &FBeamContentIdCustomization::OnIdComboBoxOpening, AsStringPropertyHandle);
	const auto IdsComboBoxSelectHandler = SNameComboBox::FOnNameSelectionChanged::CreateRaw(
		this, &FBeamContentIdCustomization::OnIdSelected, AsStringPropertyHandle);

	FString Id;
	AsStringPropertyHandle->GetValue(Id);

	FString TypeName = ContentTypeNames.Num() ? ContentTypeNames[0]->ToString() : TEXT("");
	TSharedPtr<FName> SelectedTypeName = ContentTypeNames.Num() ? ContentTypeNames[0] : TSharedPtr<FName>{};
	if (Content->GetContentTypeFromId(Id, TypeName))
	{
		SelectedTypeName = *ContentTypeNames.FindByPredicate([TypeName](TSharedPtr<FName> n)
		{
			return n->ToString().Equals(TypeName);
		});
	}

	if (SelectedTypeName.IsValid())
	{
		TSharedPtr<FName> SelectedIdName = TSharedPtr<FName>{};
		if (HasTypeFilter)
		{
			Ids = {};
			for (const auto& ContentType : ContentTypeToIdsMap)
			{
				Ids.Append(ContentType.Value);
			}
			if (Id.IsEmpty())
			{
				AsStringPropertyHandle->SetValue(Ids[0]->ToString());
				Id = Ids[0]->ToString();
			}
			for (const auto& Name : Ids)
			{
				if (Name->ToString() == Id)
					SelectedIdName = Name;
			}
		}
		else if (const auto NewIds = ContentTypeToIdsMap.Find(*SelectedTypeName); NewIds && (NewIds->Num() > 0))
		{
			if (Id.IsEmpty())
			{
				AsStringPropertyHandle->SetValue((*NewIds)[0]->ToString());
				Id = (*NewIds)[0]->ToString();
			}

			this->Ids = TArray(*NewIds);

			const auto FoundIds = ContentTypeToIdsMap.Find(*SelectedTypeName);
			if (FoundIds && FoundIds->Num() != 0)
			{
				for (const auto& Name : *FoundIds)
				{
					if (Name->ToString() == Id)
						SelectedIdName = Name;
				}

				if (!SelectedIdName.IsValid())
				{
					SelectedIdName = (*FoundIds)[0];
				}
			}
		}

		// then change the HeaderRow to add some Slate widget
		// clang-format off
		if (!HasTypeFilter)
		{
			HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
				.ValueContent()[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SAssignNew(TypeComboBox, SNameComboBox) // you can display any widget here
						                                       .ContentPadding(FMargin(6.0f, 2.0f))
 // you can stylize how you want by the way, check Slate library
						                                       .OptionsSource(&ContentTypeNames)
 // this to create all possibilities
						                                       .InitiallySelectedItem(SelectedTypeName)
 // the default or previous selected value
						                                       .OnComboBoxOpening(TypeComboBoxOpenHandler)
 // this event is defined by the SNameComboBox
						                                       .OnSelectionChanged(TypeComboBoxSelectHandler)
					]
					+ SVerticalBox::Slot()
					[
						SAssignNew(IdComboBox, SNameComboBox) // you can display any widget here
						                                     .ContentPadding(FMargin(6.0f, 2.0f))
 // you can stylize how you want by the way, check Slate library
						                                     .OptionsSource(&Ids) // this to create all possibilities
						                                     .InitiallySelectedItem(SelectedIdName)
 // the default or previous selected value
						                                     .OnComboBoxOpening(IdsComboBoxOpenHandler)
 // this event is defined by the SNameComboBox
						                                     .OnSelectionChanged(IdsComboBoxSelectHandler)
					]
				];
		}
		else
		{
			HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
				.ValueContent()[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SAssignNew(IdComboBox, SNameComboBox) // you can display any widget here
						                                     .ContentPadding(FMargin(6.0f, 2.0f))
 // you can stylize how you want by the way, check Slate library
						                                     .OptionsSource(&Ids) // this to create all possibilities
						                                     .InitiallySelectedItem(SelectedIdName)
 // the default or previous selected value
						                                     .OnComboBoxOpening(IdsComboBoxOpenHandler)
 // this event is defined by the SNameComboBox
						                                     .OnSelectionChanged(IdsComboBoxSelectHandler)
					]
				];
		}
	}
	else
	{
		HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
			.ValueContent()[
				SNew(STextBlock).Text(TAttribute(FText::FromString("No Content exists in your manifests.")))
			];
	}
}

void FBeamContentIdCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                    IDetailChildrenBuilder& StructBuilder,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	// Should customize here soon
}

void FBeamContentIdCustomization::OnTypeComboBoxOpening(const TSharedPtr<IPropertyHandle> AsStringPropertyHandle)
{
	if (AsStringPropertyHandle->IsValidHandle())
	{
		check(TypeComboBox.IsValid());
		FString Id;
		AsStringPropertyHandle->GetValue(Id);

		FString TypeName;
		if (Content->GetContentTypeFromId(Id, TypeName))
		{
			const auto SelectedName = ContentTypeNames.FindByPredicate([TypeName](TSharedPtr<FName> n)
			{
				return n->ToString().Equals(TypeName);
			});
			TypeComboBox->SetSelectedItem(*SelectedName);

			if (const auto NewIds = ContentTypeToIdsMap.Find(FName(TypeName)); NewIds && (NewIds->Num() > 0))
			{
				AsStringPropertyHandle->SetValue((*NewIds)[0]->ToString());
				this->Ids = TArray(*NewIds);
				IdComboBox->RefreshOptions();
				IdComboBox->SetSelectedItem((*NewIds)[0]);
			}
		}
	}
}

void FBeamContentIdCustomization::OnTypeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo,
                                                 const TSharedPtr<IPropertyHandle> AsStringPropertyHandle)
{
	if (AsStringPropertyHandle->IsValidHandle())
	{
		FString Id;
		AsStringPropertyHandle->GetValue(Id);

		FString TypeName;
		if (Content->GetContentTypeFromId(Id, TypeName) && !TypeName.Equals(ItemSelected->ToString()))
		{
			if (const auto NewIds = ContentTypeToIdsMap.Find(*ItemSelected); NewIds && (NewIds->Num() > 0))
			{
				AsStringPropertyHandle->SetValue((*NewIds)[0]->ToString());
				this->Ids = TArray(*NewIds);
				IdComboBox->RefreshOptions();
				IdComboBox->SetSelectedItem((*NewIds)[0]);
			}
		}
	}
}


void FBeamContentIdCustomization::OnIdComboBoxOpening(const TSharedPtr<IPropertyHandle> AsStringPropertyHandle)
{
	TSharedPtr<FName> SelectedName = GetSelectedId(AsStringPropertyHandle);
	if (SelectedName.IsValid())
	{
		if (!HasTypeFilter)
		{
			check(TypeComboBox.IsValid());
		}
		IdComboBox->RefreshOptions();
		IdComboBox->SetSelectedItem(SelectedName);
	}
}

void FBeamContentIdCustomization::OnIdSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo,
                                               const TSharedPtr<IPropertyHandle> AsStringPropertyHandle)
{
	if (ItemSelected.IsValid())
	{
		AsStringPropertyHandle->SetValue(ItemSelected->ToString());
	}
}

TSharedPtr<FName> FBeamContentIdCustomization::GetSelectedId(
	const TSharedPtr<IPropertyHandle> AsStringPropertyHandle) const
{
	const int32 TypeCount = ContentTypeNames.Num();
	const int32 IdsCount = ContentTypeToIdsMap.Num();
	if (TypeCount <= 0 || IdsCount <= 0)
	{
		return NULL;
	}

	FString Id;
	AsStringPropertyHandle->GetValue(Id);

	FString TypeName;
	if (Content->GetContentTypeFromId(Id, TypeName))
	{
		const auto FoundIds = ContentTypeToIdsMap.Find(FName(TypeName));
		if (!FoundIds || FoundIds->Num() == 0) return NULL;

		for (const auto& Name : *FoundIds)
		{
			if (Name->ToString() == Id)
				return Name;
		}

		return (*FoundIds)[0];
	}

	return NULL;
}

void FBeamContentIdCustomization::GetContentOptions(TArray<TSharedPtr<FName>>& TypeNames,
                                                    TMap<FName, TArray<TSharedPtr<FName>>>& PerTypeNameIds)
{
	Content->GetContentTypeToIdMaps(PerTypeNameIds);
	TArray<FName> Names;
	PerTypeNameIds.GetKeys(Names);
	for (const auto& Name : Names)
	{
		if (!TypeNames.ContainsByPredicate([Name](TSharedPtr<FName> N)
		{
			return N->ToString().Equals(Name.ToString());
		}))
		{
			TypeNames.Add(MakeShareable(new FName(Name)));
		}
	}
}

#undef LOCTEXT_NAMESPACE
