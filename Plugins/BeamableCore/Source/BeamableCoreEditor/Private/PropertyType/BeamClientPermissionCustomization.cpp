#include "PropertyType/BeamClientPermissionCustomization.h"

#include "DetailWidgetRow.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/RequestType.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"

#define LOCTEXT_NAMESPACE "RequestTypeCustomization"

TSharedRef<IPropertyTypeCustomization> FBeamClientPermissionCustomization::MakeInstance()
{
	// Create the instance and returned a SharedRef
	return MakeShareable(new FBeamClientPermissionCustomization());
}

void FBeamClientPermissionCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s - The header customization is called"), ANSI_TO_TCHAR(__FUNCTION__));
	// Get the property handler of the type property:

	void* ValuePtr = nullptr;
	FBeamClientPermission* ClientPermissionPtr = nullptr;
	if (StructPropertyHandle->GetValueData(ValuePtr) != FPropertyAccess::Fail)
	{
		ClientPermissionPtr = static_cast<FBeamClientPermission*>(ValuePtr);
	}

	const TSharedPtr<IPropertyHandle> BoolPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBeamClientPermission, AsBool));
	const TSharedPtr<IPropertyHandle> StringPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBeamClientPermission, AsString));
	check(BoolPropertyHandle.IsValid());
	check(StringPropertyHandle.IsValid());

	// then change the HeaderRow to add some Slate widget
	// clang-format off
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
		.ValueContent()[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(Checkbox, SCheckBox)
				.OnCheckStateChanged(FOnCheckStateChanged::CreateLambda(
					[this, StructPropertyHandle, ClientPermissionPtr](ECheckBoxState NewState)
					{
						const bool bIsChecked = NewState == ECheckBoxState::Checked;

						StructPropertyHandle->NotifyPreChange();
						ClientPermissionPtr->Set(&bIsChecked, TNameOf<bool>::GetName());
						StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
					}))
			]
		];

	StructPropertyHandle->SetOnPropertyResetToDefault(FSimpleDelegate::CreateLambda([this, ClientPermissionPtr]
	{
		Checkbox->SetIsChecked(ClientPermissionPtr->AsBool ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}));
	Checkbox->SetIsChecked(ClientPermissionPtr->AsBool ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void FBeamClientPermissionCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder,
                                                           IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	// Should customize here soon
}

#undef LOCTEXT_NAMESPACE
