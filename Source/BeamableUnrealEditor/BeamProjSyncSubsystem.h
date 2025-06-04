// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectoryWatcherModule.h"
#include "IDirectoryWatcher.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "BeamProjSyncSubsystem.generated.h"

/**
 * This editor subsystem is responsible for synchronizing any change you make while in a particular BEAMPROJ_ to that project's Overrides folder.
 * This is true for the directories in the OverridenDirectories list.
 *
 * Practically this means that:
 *  - If your project is set to BEAMPROJ_Sandbox, the Config and .beamable/content folders will be mirrored to what's in the Plugins/BEAMPROJ_Sandbox/Overrides directories.
 *  - If your project is set to BEAMPROJ_HathoraDemo, the Config and .beamable/content folders will be mirrored to what's in the Plugins/BEAMPROJ_HathoraDemo/Overrides directories.
 *
 * For all intents and purposes, this makes it so that we effectively have "N- Unreal projects" inside this repo.
 * For more information on how this is applied, go look at BeamableUnreal.Target.cs's variours ConfigureIf functions.
 */
UCLASS()
class BEAMABLEUNREALEDITOR_API UBeamProjSyncSubsystem : public UBeamEditorSubsystem
{
	GENERATED_BODY()

public:
	// UPROPERTY(BlueprintReadOnly)
	// FString ActiveBeamProj;

	bool SyncAllOverridenDirectories() const;

	inline static TArray<FString> IgnoreDirectories = {TEXT("content"), TEXT("temp")};

private:
	inline static TArray<FString> OverridenDirectories = {TEXT("Config"), TEXT(".beamable")};
	inline static TArray<FDelegateHandle> OverridenDirectoriesHandlers = {{}, {}};
	inline static FString KBeamProj_Sandbox = "BEAMPROJ_Sandbox";

	UPROPERTY()
	UBeamEditorContent* EditorContent;

	// FDelegateHandle OnContentSavedHandle;
	// FDelegateHandle OnUndoRedoHandle;
	// FDelegateHandle OnPreBeginPIEHandle;	


	FString UnrealConfigDir() { return OverridenDirectories[0]; }
	FString BeamableContentDir() { return OverridenDirectories[1]; }


	void GetPaths(const FString& OverridenDirectory, FString& WatchDir, FString& TargetDir, FString& AbsWatchDir, FString& AbsTargetDir) const;

	FString GetActiveBeamProj() const;

	void ApplyProjectOverrides(const FString& BeamProj) const;

	void CopyDirectory(const FString& SourceDir, const FString& DestinationDir) const;
};
