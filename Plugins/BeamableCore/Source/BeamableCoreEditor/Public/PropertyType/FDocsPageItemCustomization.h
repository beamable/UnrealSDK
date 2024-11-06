#pragma once
#include "DetailWidgetRow.h"
#include "Subsystems/BeamEditor.h"

class FDocsPageItemCustomization : public IPropertyTypeCustomization
{
public:
	/**
	 * It is just a convenient helpers which will be used
	 * to register our customization. When the propertyEditor module
	 * find our FMyStruct property, it will use this static method
	 * to instantiate our customization object.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		UBeamEditor* BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();

		// Create the instance and returned a SharedRef
		FDocsPageItemCustomization* NavItem = new FDocsPageItemCustomization();
		// NavItem->NavItems = BeamEditor->NavItems;
		NavItem->NavItemOptions.Empty();
		for(int32 i = 0; i < BeamEditor->DocsPages.Num(); i++)
		{
			FDocsPageItem* Item = new FDocsPageItem(BeamEditor->DocsPages[i]);
			// NavItem->Ids.Push(MakeShareable<FName>(new FName(*NavItem->NavItems[i].Id)));
			NavItem->NavItemOptions.Add(MakeShareable(Item));
		}
		return MakeShareable(NavItem);
	}

	// BEGIN IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
												  FDetailWidgetRow& HeaderRow,
												  IPropertyTypeCustomizationUtils& StructCustomizationUtils) override
	{
		StructPropertyHandle = PropertyHandle;
		
		// Get the current value

		TSharedPtr<IPropertyHandle> IdHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDocsPageItem, Id));
		TSharedPtr<IPropertyHandle> PathHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDocsPageItem, Path));

		FString CurrentId;
		FString CurrentPath;
		IdHandle->GetValue(CurrentId);
		PathHandle->GetValue(CurrentPath);

		// Find the currently selected item
		TSharedPtr<FDocsPageItem> InitiallySelectedItem;
		for (const TSharedPtr<FDocsPageItem>& Item : NavItemOptions)
		{
			if (Item->Id == CurrentId && Item->Path == CurrentPath)
			{
				InitiallySelectedItem = Item;
				break;
			}
		}
		DisplayName = FText::FromString(InitiallySelectedItem.IsValid() ? InitiallySelectedItem->Id : TEXT("Select a Nav Item"));
		
		NavItemComboBox = SNew(SComboBox<TSharedPtr<FDocsPageItem>>)
			.OptionsSource(&NavItemOptions)
			.OnSelectionChanged(this, &FDocsPageItemCustomization::OnNavItemChanged)
			.OnGenerateWidget(this, &FDocsPageItemCustomization::MakeNavItemWidget)
			.InitiallySelectedItem(InitiallySelectedItem)
			[
				SNew(STextBlock)
				.Text_Lambda([this]() -> FText
				{
					return DisplayName;
				})
			];

		// Add the combo box to the header row
		HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MaxDesiredWidth(0)
		[
			NavItemComboBox.ToSharedRef()
		];
	}
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}

	void OnNavItemChanged(TSharedPtr<FDocsPageItem> NewValue, ESelectInfo::Type SelectInfo)
	{
		if (NewValue.IsValid())
		{
			TSharedPtr<IPropertyHandle> IdHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDocsPageItem, Id));
			TSharedPtr<IPropertyHandle> PathHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDocsPageItem, Path));

			IdHandle->SetValue(NewValue->Id);
			PathHandle->SetValue(NewValue->Path);
			DisplayName = FText::FromString(NewValue->Id);

			// Update the combo box display text
			NavItemComboBox->RefreshOptions();
			NavItemComboBox->SetSelectedItem(NewValue);
		}
	}
	
	TSharedRef<SWidget> MakeNavItemWidget(TSharedPtr<FDocsPageItem> InItem)
	{
		return SNew(STextBlock)
			.Text(FText::FromString(InItem.IsValid() ? InItem->Id : TEXT("Invalid Item")));
	}
	// END IPropertyTypeCustomization interface

	TSharedPtr<IPropertyHandle> StructPropertyHandle;
	TSharedPtr<SComboBox<TSharedPtr<FDocsPageItem>>> NavItemComboBox;
	TArray<TSharedPtr<FDocsPageItem>> NavItemOptions;
	FText DisplayName;
};
