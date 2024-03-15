#pragma once

#include "SNameComboBox.h"
#include "IPropertyTypeCustomization.h"

class FRequestTypeCustomization : public IPropertyTypeCustomization
{
public:
	/**
	 * It is just a convenient helpers which will be used
	 * to register our customization. When the propertyEditor module
	 * find our FMyStruct property, it will use this static method
	 * to instantiate our customization object.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	// BEGIN IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;	
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	// END IPropertyTypeCustomization interface

	
	TSharedPtr<SNameComboBox> NameComboBox;

	inline static TArray<TSharedPtr<FName>> AttributesList = TArray<TSharedPtr<FName>>{};
	static void GetNames(TArray<TSharedPtr<FName>>& ShareableNames);
};
