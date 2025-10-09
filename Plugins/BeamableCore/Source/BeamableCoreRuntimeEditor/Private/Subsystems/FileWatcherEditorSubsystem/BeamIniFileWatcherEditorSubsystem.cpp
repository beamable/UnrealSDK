// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FileWatcherEditorSubsystem/BeamIniFileWatcherEditorSubsystem.h"

#include "BeamCoreSettings.h"
#include "DirectoryWatcherModule.h"
#include "IDirectoryWatcher.h"
#include "Subsystems/BeamEditor.h"

void UBeamIniFileWatcherEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FString ConfigDir = FPaths::ProjectConfigDir();

	RegisterWatcher(ConfigDir, ConfigWatcherHandle);

	FString SavedDir = FPaths::ProjectSavedDir();
	
	RegisterWatcher(SavedDir, SavedConfigWatcherHandle);
}

void UBeamIniFileWatcherEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FString ConfigDir = FPaths::ProjectConfigDir();

	UnregisterWatcher(ConfigDir, ConfigWatcherHandle);

	FString SavedDir = FPaths::ProjectSavedDir();
	
	UnregisterWatcher(SavedDir, SavedConfigWatcherHandle);
}

void UBeamIniFileWatcherEditorSubsystem::OnIniFileChanged(FString IniConfigName)
{
	UClass* BeamCoreSettings = GetDefault<UBeamCoreSettings>()->GetClass();
	if (IniConfigName.StartsWith("Default"))
	{
		IniConfigName.RemoveFromStart("Default");
	}
	if (IniConfigName == BeamCoreSettings->ClassConfigName.ToString())
	{
		if (GEngine->GetEngineSubsystem<UBeamEnvironment>()->RefreshEnvData())
		{
			GEditor->GetEditorSubsystem<UBeamEditor>()->SignOut();
		}
	}
}


void UBeamIniFileWatcherEditorSubsystem::OnIniDirectoryChanged(const TArray<FFileChangeData>& FileChanges)
{
	for (const FFileChangeData& Change : FileChanges)
	{
		FString Extension = FPaths::GetExtension(Change.Filename);
		if ( Extension == "ini" && Change.Action == FFileChangeData::FCA_Modified)
		{
			OnIniFileChanged(FPaths::GetBaseFilename(Change.Filename));
		}
	}
}

void UBeamIniFileWatcherEditorSubsystem::RegisterWatcher(FString Path, FDelegateHandle& OutDelegateHandler)
{
	FDirectoryWatcherModule& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>("DirectoryWatcher");
	IDirectoryWatcher* DirectoryWatcher = DirectoryWatcherModule.Get();

	if (DirectoryWatcher)
	{
		DirectoryWatcher->RegisterDirectoryChangedCallback_Handle(
			Path,
			IDirectoryWatcher::FDirectoryChanged::CreateUObject(this, &UBeamIniFileWatcherEditorSubsystem::OnIniDirectoryChanged),
			OutDelegateHandler,
			IDirectoryWatcher::WatchOptions::IncludeDirectoryChanges
		);
	}
}

void UBeamIniFileWatcherEditorSubsystem::UnregisterWatcher(FString Path, FDelegateHandle DelegateHandler)
{
	if (IDirectoryWatcher* DirectoryWatcher = FModuleManager::GetModuleChecked<FDirectoryWatcherModule>("DirectoryWatcher").Get())
	{
		DirectoryWatcher->UnregisterDirectoryChangedCallback_Handle(Path, DelegateHandler);
	}
}
