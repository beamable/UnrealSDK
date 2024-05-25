// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectoryWatcherModule.h"
#include "IDirectoryWatcher.h"
#include "Editor/TransBuffer.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/Content/BeamEditorContent.h"
#include "BeamProjSyncSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLEUNREALEDITOR_API UBeamProjSyncSubsystem : public UBeamEditorSubsystem
{
	GENERATED_BODY()

	inline static TArray<FString> OverridenDirectories = {TEXT("Config"), TEXT("./beamable/content")};
	inline static TArray<FDelegateHandle> OverridenDirectoriesHandlers = {{}, {}};


	UPROPERTY()
	UBeamEditorContent* EditorContent;

	FDelegateHandle OnContentSavedHandle;
	FDelegateHandle OnUndoRedoHandle;

	FString ActiveBeamProj;

	FString UnrealConfigDir() { return OverridenDirectories[0]; }
	FString BeamableContentDir() { return OverridenDirectories[1]; }


	virtual FBeamOperationHandle InitializeWhenEditorReady() override
	{
		TArray<FName> Modules;
		TArray<FString> ModulesStr;
		FModuleManager::Get().FindModules(TEXT("BEAMPROJ*"), Modules);
		for (auto Module : Modules) ModulesStr.Add(Module.ToString());

		if (ModulesStr.Num() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Found no loaded BEAMPROJ module."));
			return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
		}

		if (ModulesStr.Num() > 1)
		{
			UE_LOG(LogTemp, Error, TEXT("Found more than one loaded BEAMPROJ module. LOADED=[%s]."), *FString::Join(ModulesStr, TEXT(",")));
			return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
		}

		// Get the active BeamProj
		ActiveBeamProj = ModulesStr[0];

		// Listen for content changes and keep them in-sync
		EditorContent = GEditor->GetEditorSubsystem<UBeamEditorContent>();
		OnContentSavedHandle = EditorContent->OnContentSaved.AddUObject(this, &ThisClass::OnContentSaved);

		// Listen for file-system-level changes in all relevant directories 
		FDirectoryWatcherModule& DirectoryWatcherModule = FModuleManager::Get().LoadModuleChecked<FDirectoryWatcherModule>(TEXT("DirectoryWatcher"));
		IDirectoryWatcher* DirectoryWatcher = DirectoryWatcherModule.Get();

		for (int i = 0; i < OverridenDirectories.Num(); ++i)
		{
			const auto OverridenDirectory = OverridenDirectories[i];

			FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
			GetPaths(OverridenDirectory, WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

			const auto OnChanged = IDirectoryWatcher::FDirectoryChanged::CreateLambda([this, AbsWatchDir, AbsTargetDir](const TArray<FFileChangeData>& FileChanges)
			{
				IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
				PlatformFile.CopyDirectoryTree(*AbsTargetDir, *AbsWatchDir, true);
				UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
			});

			if (IFileManager::Get().DirectoryExists(*AbsWatchDir))
			{
				DirectoryWatcher->RegisterDirectoryChangedCallback_Handle(AbsWatchDir, OnChanged, OverridenDirectoriesHandlers[i], IDirectoryWatcher::WatchOptions::IncludeDirectoryChanges);
			}
		}

		// Listen for undo/redo
		if (UTransBuffer* Transactor = Cast<UTransBuffer>(GEditor->Trans))
		{
			OnUndoRedoHandle = Transactor->OnTransactionStateChanged().AddUObject(this, &ThisClass::OnObjectRedoUndo);
		}

		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	void GetPaths(const FString& OverridenDirectory, FString& WatchDir, FString& TargetDir, FString& AbsWatchDir, FString& AbsTargetDir) const
	{
		WatchDir = FPaths::ProjectDir() / OverridenDirectory;
		TargetDir = FPaths::ProjectDir() / TEXT("Plugins") / ActiveBeamProj / TEXT("Overrides") / OverridenDirectory;

		AbsWatchDir = FPaths::IsRelative(WatchDir) ? FPaths::ConvertRelativePathToFull(WatchDir) : WatchDir;
		AbsTargetDir = FPaths::IsRelative(TargetDir) ? FPaths::ConvertRelativePathToFull(TargetDir) : TargetDir;
	}


	virtual void Deinitialize() override
	{
		// Stop listening to the content system
		if (EditorContent)
			EditorContent->OnContentSaved.Remove(OnContentSavedHandle);

		// Stop listening for changes from the file system
		FDirectoryWatcherModule& DirectoryWatcherModule = FModuleManager::Get().LoadModuleChecked<FDirectoryWatcherModule>(TEXT("DirectoryWatcher"));
		IDirectoryWatcher* DirectoryWatcher = DirectoryWatcherModule.Get();

		for (int i = 0; i < OverridenDirectories.Num(); ++i)
		{
			const auto OverridenDirectory = OverridenDirectories[i];

			const auto WatchDir = FPaths::ProjectDir() / OverridenDirectory;
			const auto AbsWatchDir = FPaths::IsRelative(WatchDir) ? FPaths::ConvertRelativePathToFull(WatchDir) : WatchDir;

			if (IFileManager::Get().DirectoryExists(*AbsWatchDir))
			{
				DirectoryWatcher->UnregisterDirectoryChangedCallback_Handle(AbsWatchDir, OverridenDirectoriesHandlers[i]);
			}
		}

		// Stop listening for undo/redo
		if (UTransBuffer* Transactor = Cast<UTransBuffer>(GEditor->Trans))
		{
			Transactor->OnTransactionStateChanged().Remove(OnUndoRedoHandle);
		}
	}

	void OnObjectRedoUndo(const FTransactionContext& TransactionContext, ETransactionStateEventType TransactionState)
	{
		if (TransactionState == ETransactionStateEventType::UndoRedoFinalized)
		{
			FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
			GetPaths(UnrealConfigDir(), WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
			PlatformFile.CopyDirectoryTree(*AbsTargetDir, *AbsWatchDir, true);
			UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
		}
	}

	void OnContentSaved(FBeamContentManifestId ManifestId, FBeamContentId Id)
	{
		FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
		GetPaths(BeamableContentDir(), WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		PlatformFile.CopyDirectoryTree(*AbsTargetDir, *AbsWatchDir, true);
		UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
	}
};
