// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"
#include "SGraphPinComboBox.h"
#include "SNameComboBox.h"

/**
 * 
 */
class BEAMABLECOREEDITOR_API SOptionalTypePin : public SGraphPin
{
	inline const static FString UnrealBoolType = TEXT("bool");
	inline const static FString UnrealByteType = TEXT("uint8");
	inline const static FString UnrealIntType = TEXT("int32");
	inline const static FString UnrealInt64Type = TEXT("int64");
	inline const static FString UnrealFloatType = TEXT("float");
	inline const static FString UnrealDoubleType = TEXT("double");
	inline const static FString UnrealStringType = TEXT("FString");
	
	inline const static TArray<FString> CanProvideTextBoxDefaultTypes{
		UnrealBoolType,
		UnrealByteType,
		UnrealIntType,
		UnrealInt64Type,
		UnrealFloatType,
		UnrealDoubleType,
		UnrealStringType
	};


public:
	SLATE_BEGIN_ARGS(SOptionalTypePin)
		{
		}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	
	// this override is used to display slate widget used for customization.
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	
	FString GetOptionalType();
	FString BuildDefaultValueString();
	void OnCheckboxChanged(ECheckBoxState CheckBoxState);
	void OnTextDefaultChanged(const FText& Text);
	void OnComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type /*SelectInfo*/);	

	virtual FSlateColor GetPinColor() const override;
	virtual EVisibility GetDefaultValueVisibility() const override;

private:
	
	
	TSharedPtr<SHorizontalBox> HorizontalBox;
	TSharedPtr<SCheckBox> OptionalCheckBox;
	TSharedPtr<SPinComboBox> EnumValuesComboBox;
	
	UEnum* OptionalEnumType;	
	FString OptionalDefaultValue;	
};
