#pragma once

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyTypeCustomization.h"
#include "IPropertyUtilities.h"
#include "Serialization/BeamOptional.h"


class FBeamOptionalCustomization : public IPropertyTypeCustomization
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
		// Create the instance and returned a SharedRef
		return MakeShareable(new FBeamOptionalCustomization());
	}

	// BEGIN IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));

		// Get the property handler of the type property:
		void* ValuePtr = nullptr;
		FBeamOptional* Optional = nullptr;
		if (StructPropertyHandle->GetValueData(ValuePtr) != FPropertyAccess::Fail)
		{
			Optional = static_cast<FBeamOptional*>(ValuePtr);
		}

		// Find the Val property
		const auto ValPropertyHandle = StructPropertyHandle->GetChildHandle(FName("Val"));
		check(ValPropertyHandle.IsValid());

		// then change the HeaderRow to add some Slate widget
		HeaderRow
			.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
			.ValueContent()[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(Checkbox, SCheckBox)
					.OnCheckStateChanged(FOnCheckStateChanged::CreateLambda(
						[this, Optional, &StructCustomizationUtils, StructPropertyHandle](ECheckBoxState NewState)
						{
							StructPropertyHandle->NotifyPreChange();
							const bool bIsChecked = NewState == ECheckBoxState::Checked;
							Optional->IsSet = bIsChecked;

							StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
							StructPropertyHandle->NotifyFinishedChangingProperties();

							StructCustomizationUtils.GetPropertyUtilities()->RequestForceRefresh();
						}))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.Visibility_Lambda([Optional]
					{
						return Optional->IsSet ? EVisibility::Visible : EVisibility::Hidden;
					})
					[
						ValPropertyHandle->CreatePropertyValueWidget()
					]
				]
			];

		ValPropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([&StructCustomizationUtils]()
		{
			StructCustomizationUtils.GetPropertyUtilities()->RequestForceRefresh();
		}));

		Checkbox->SetIsChecked(Optional->IsSet ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}


	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override
	{
		const auto ValPropertyHandle = StructPropertyHandle->GetChildHandle(FName("Val"));
		check(ValPropertyHandle.IsValid());

		if (!Checkbox->IsChecked())
		{
			return;
		}
		// Check if the type is a instanced propety, if it is we need to handle as a different case.
		bool IsInstanced = false;
		if (FProperty* Property = ValPropertyHandle->GetProperty())
		{
			if (FObjectProperty* ObjectProp = CastField<FObjectProperty>(Property))
			{
				if (ObjectProp->HasAnyPropertyFlags(CPF_InstancedReference))
				{
					IsInstanced = true;
				}
			}
		}

		uint32 NumChildren;
		ValPropertyHandle->GetNumChildren(NumChildren);

		for (uint32 i = 0; i < NumChildren; ++i)
		{
			TSharedPtr<IPropertyHandle> ChildHandle = ValPropertyHandle->GetChildHandle(i);

			// If its a instanced property I need to get the child 0 to draw correctly
			if (IsInstanced)
			{
				ChildHandle = ChildHandle->GetChildHandle(0);
			}

			if (ChildHandle.IsValid() && ChildHandle->IsValidHandle())
			{
				StructBuilder.AddProperty(ChildHandle.ToSharedRef());
			}
		}
	}

	// END IPropertyTypeCustomization interface

	TSharedPtr<SCheckBox> Checkbox;
};
