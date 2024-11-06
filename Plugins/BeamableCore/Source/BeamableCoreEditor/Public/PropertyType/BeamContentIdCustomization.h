#pragma once

#include "SNameComboBox.h"
#include "IPropertyTypeCustomization.h"
#include "Subsystems/Content/BeamEditorContent.h"


class FBeamContentIdCustomization : public IPropertyTypeCustomization
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

	
	static UBeamEditorContent* Content;	
	static TArray<TSharedPtr<FName>> ContentTypeNames;
	static TMap<FName, TArray<TSharedPtr<FName>>> ContentTypeToIdsMap;

	TArray<TSharedPtr<FName>> Ids;


	TSharedPtr<SVerticalBox> WidgetContainer;

	TSharedPtr<SNameComboBox> TypeComboBox;
	TSharedPtr<SNameComboBox> IdComboBox;
	bool HasTypeFilter;
	bool OnlyExplicitTypes;

	void OnTypeComboBoxOpening(const TSharedPtr<IPropertyHandle> AsStringPropertyHandle);
	void OnTypeSelected(TSharedPtr<FName> ItemSelected, ::ESelectInfo::Type SelectInfo, const TSharedPtr<IPropertyHandle> AsStringPropertyHandle);


	void OnIdComboBoxOpening(const TSharedPtr<IPropertyHandle> AsStringPropertyHandle);
	void OnIdSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo, const TSharedPtr<IPropertyHandle> AsStringPropertyHandle);


	TSharedPtr<FName> GetSelectedId(const TSharedPtr<IPropertyHandle> AsStringPropertyHandle) const;


	static void GetContentOptions(TArray<TSharedPtr<FName>>& Array, TMap<FName, TArray<TSharedPtr<FName>>>& Map);
};
