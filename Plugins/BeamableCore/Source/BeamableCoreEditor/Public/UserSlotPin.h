// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"
#include "SNameComboBox.h"

/**
 * 
 */
class BEAMABLECOREEDITOR_API SUserSlotPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SUserSlotPin) {}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	// this override is used to display slate widget used for customization.
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	void OnAttributeSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();
	
	TSharedPtr<FName> GetSelectedName() const;

	void SetPropertyWithName(const FName& Name);
	void GetPropertyAsName(FName& OutName) const;

	virtual EVisibility GetDefaultValueVisibility() const override;

private:
	TArray<TSharedPtr<FName>> AttributesList;
	TSharedPtr<SNameComboBox> NameComboBox;

	/**
	 * This function is allow to convert each setting name to
	 * TSharedPtr which our Pin object can works on.
	 */
	void GetNames(TArray<TSharedPtr<FName>>& ShareableNames) const;
};
