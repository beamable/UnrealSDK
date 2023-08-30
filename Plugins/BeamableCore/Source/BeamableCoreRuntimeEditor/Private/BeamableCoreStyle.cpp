// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamableCoreStyle.h"

#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "EditorStyleSet.h"
#include "Interfaces/IPluginManager.h"

FPluginStyleSet::FPluginStyleSet(const FName& InPluginName, const FName& InStyleSetName)
	: FSlateStyleSet(InStyleSetName == NAME_None ? InPluginName : FName(*(InPluginName.ToString() + TEXT(".") + InStyleSetName.ToString())))
{
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName.ToString());
	check(Plugin.IsValid());

	SetContentRoot(Plugin->GetContentDir());
	SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

FBeamableCoreStyle::FBeamableCoreStyle() : FPluginStyleSet(TEXT("BeamableCore"))
{
	const FVector2D IconSize(20.0f, 20.0f);
	const FVector2D SmallIconSize(20.0f, 20.0f);
	const FVector2D LabelIconSize(16.0f, 16.0f);

	Set("BeamIcon", new FSlateImageBrush(RootToContentDir(TEXT("BeamIcon.png")), Icon20x20));
	Set("BeamIconSpaceship", new FSlateImageBrush(RootToContentDir(TEXT("BeamSpaceship.png")), Icon40x40));	

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FBeamableCoreStyle::~FBeamableCoreStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

FBeamableCoreStyle& FBeamableCoreStyle::Get()
{
	static FBeamableCoreStyle Inst;
	return Inst;
}
