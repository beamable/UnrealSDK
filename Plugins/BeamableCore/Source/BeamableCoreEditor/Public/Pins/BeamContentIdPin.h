// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"
#include "SNameComboBox.h"
#include "Subsystems/Content/BeamEditorContent.h"

/**
 * 
 */
class BEAMABLECOREEDITOR_API SBeamContentIdPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SBeamContentIdPin) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:

	UPROPERTY()
	UBeamEditorContent* Content = nullptr;

	
	
	// this override is used to display slate widget used for customization.
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	void OnIdSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnTypeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
	
	void OnTypeComboBoxOpening();
	void OnIdComboBoxOpening();
	
	TSharedPtr<FName> GetSelectedId() const;
	TSharedPtr<FName> GetSelectedType() const;
	TArray<TSharedPtr<FName>>* GetIdsForSelectedType() const;

	void SetPropertyWithName(const FName& Name);
	void GetPropertyAsName(FName& OutName) const;

	virtual EVisibility GetDefaultValueVisibility() const override;

private:
	TArray<TSharedPtr<FName>> Ids;
	TArray<TSharedPtr<FName>> ContentTypeNames;
	TMap<FName, TArray<TSharedPtr<FName>>> ContentTypeToIdsMap;

	TSharedPtr<SVerticalBox> WidgetContainer;
	
	TSharedPtr<SNameComboBox> TypeComboBox;
	TSharedPtr<SNameComboBox> IdComboBox;
	

	/**
	 * This function is allow to convert each setting name to
	 * TSharedPtr which our Pin object can works on.
	 */
	void GetContentOptions(TArray<TSharedPtr<FName>>& TypeNames, TMap<FName, TArray<TSharedPtr<FName>>>& PerTypeNameIds) const;
};
