#pragma once

#include "DetailWidgetRow.h"
#include "IPropertyTypeCustomization.h"


template <typename T>
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
		UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));

		// Get the property handler of the type property:
		void* ValuePtr = nullptr;
		T*    Optional = nullptr;
		if (StructPropertyHandle->GetValueData(ValuePtr) != FPropertyAccess::Fail)
		{
			Optional = static_cast<T*>(ValuePtr);
		}

		// Find the Val property
		const auto ValPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(T, Val));
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
						[this, Optional](ECheckBoxState NewState)
						{
							const bool bIsChecked = NewState == ECheckBoxState::Checked;
							Optional->IsSet       = bIsChecked;
						}))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()[
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

		Checkbox->SetIsChecked(Optional->IsSet ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}

	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override
	{
	}

	// END IPropertyTypeCustomization interface

	TSharedPtr<SCheckBox> Checkbox;
};
