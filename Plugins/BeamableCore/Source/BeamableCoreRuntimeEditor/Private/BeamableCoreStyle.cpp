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

	Set("BeamIcon_AutoGenRequests", new FSlateImageBrush(RootToContentDir(TEXT("Editor/Icons/IconBeamNode_AutoGenRequests.png")), Icon20x20));
	Set("BeamIcon_Operations", new FSlateImageBrush(RootToContentDir(TEXT("Editor/Icons/IconBeamNode_Operations.png")), Icon20x20));
	Set("BeamIcon_ResyncProj", new FSlateImageBrush(RootToContentDir(TEXT("Editor/Icons/IconBeam_Download.png")), Icon40x40));
	Set("BeamIcon", new FSlateImageBrush(RootToContentDir(TEXT("Editor/Icons/IconBeam_Beamable.png")), Icon40x40));
	Set("BeamIconSmall", new FSlateImageBrush(RootToContentDir(TEXT("Editor/Icons/IconBeam_Beamable.png")), Icon20x20));

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
