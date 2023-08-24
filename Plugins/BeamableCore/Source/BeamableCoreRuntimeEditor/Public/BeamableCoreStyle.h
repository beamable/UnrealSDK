// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

/**
 * 
 */
class FPluginStyleSet : public FSlateStyleSet
{
public:
	FPluginStyleSet(const FName& InPluginName, const FName& InStyleSetName = NAME_None);
};

/**
 * 
 */
class BEAMABLECORERUNTIMEEDITOR_API FBeamableCoreStyle : public FPluginStyleSet
{
public:
	/** Access the singleton instance for this style set */
	static FBeamableCoreStyle& Get();

private:
	FBeamableCoreStyle();
	~FBeamableCoreStyle();
};
