// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "IDirectoryWatcher.h"
#include "BeamIniFileWatcherEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIMEEDITOR_API UBeamIniFileWatcherEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
	FDelegateHandle ConfigWatcherHandle;
	FDelegateHandle SavedConfigWatcherHandle;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual void OnIniFileChanged(FString IniConfigName);
private:

	void OnIniDirectoryChanged(const TArray<FFileChangeData>& FileChanges);

	void RegisterWatcher(FString Path, FDelegateHandle& OutDelegateHandler);
	void UnregisterWatcher(FString Path, FDelegateHandle DelegateHandler);

};
