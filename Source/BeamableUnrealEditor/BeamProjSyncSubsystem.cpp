// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamProjSyncSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Misc/OutputDeviceDebug.h"

static bool CopyDirectoryRecursive(const FString& SourceDir, const FString& DestDir)
{
	IFileManager& FileManager = IFileManager::Get();

	// Normalize directory paths (ensure trailing slash)
	FString NormalizedSource = FPaths::ConvertRelativePathToFull(SourceDir) + TEXT("/");
	FString NormalizedDest = FPaths::ConvertRelativePathToFull(DestDir) + TEXT("/");

	// Get all files and directories recursively from the source
	TArray<FString> FoundFilesAndDirs;
	FileManager.FindFilesRecursive(FoundFilesAndDirs, *NormalizedSource, TEXT("*"), true, true);

	for (const FString& Path : FoundFilesAndDirs)
	{
		// Get relative path to recreate structure in destination
		FString RelativePath = Path;
		FPaths::MakePathRelativeTo(RelativePath, *NormalizedSource);

		// Check if any part of the relative path contains "/temp/" or ends with "/temp"
		TArray<FString> PathParts;
		RelativePath.ParseIntoArray(PathParts, TEXT("/"), true);
		if (!PathParts.Contains(TEXT("temp")))
		{
			FString TargetPath = FPaths::Combine(NormalizedDest, RelativePath);

			if (FileManager.DirectoryExists(*Path))
			{
				FileManager.MakeDirectory(*TargetPath, true);
			}
			else if (FileManager.FileExists(*Path))
			{
				FString TargetDir = FPaths::GetPath(TargetPath);
				FileManager.MakeDirectory(*TargetDir, true); // Ensure folder exists

				IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();	

				if (!platformFile.CopyFile(*TargetPath, *Path ))
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to copy file: %s , %s"), *Path, *TargetPath);
					return false;
				}
			}
		}
	}

	return true;
}

FBeamOperationHandle UBeamProjSyncSubsystem::InitializeWhenEditorReady()
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
	FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Docs/mkdocs.yml"));

	// Check if the file exists
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File does not exist: %s"), *FilePath);
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	// Read the file into an array of strings, one per line
	TArray<FString> Lines;
	if (!FFileHelper::LoadFileToStringArray(Lines, *FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read file: %s"), *FilePath);
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	TArray<FDocsPageItem> NavItems;
	bool bNavSectionFound = false;
	int32 NavIndentation = 0;
	FString CategoryId;
	// Iterate over the lines
	for (int32 i = 0; i < Lines.Num(); ++i)
	{
		FString Line = Lines[i];

		// Ignore all lines until we find 'nav:'
		if (!bNavSectionFound)
		{
			if (Line.TrimStart().StartsWith(TEXT("nav:")))
			{
				bNavSectionFound = true;
				NavIndentation = Line.Len() - Line.TrimStart().Len();
			}
			continue;
		}
		int32 CurrentIndentation = Line.Len() - Line.TrimStart().Len();

		// Only process lines until they are indented more than the 'nav:' line
		if (CurrentIndentation <= NavIndentation)
		{
			break;
		}

		// Use regex to extract id and path
		// Pattern matches lines like:
		// - Title: 'path/to/file.md'
		// - Title: "path/to/file.md"
		// - Title: path/to/file.md
		FRegexPattern Pattern(TEXT(R"(^\s*-\s*(.+?):\s*(?:'|")?(.*?)(?:\.md)?(?:'|")?$)"));
		FRegexMatcher Matcher(Pattern, Line);

		if (Matcher.FindNext())
		{
			FString Id = Matcher.GetCaptureGroup(1).TrimStartAndEnd();
			FString Path = Matcher.GetCaptureGroup(2).TrimStartAndEnd();

			// Remove any surrounding quotes from Path
			Path = Path.Replace(TEXT("'"), TEXT("")).Replace(TEXT("\""), TEXT(""));

			// Remove .md suffix if present
			if (Path.EndsWith(TEXT(".md")))
			{
				Path = Path.LeftChop(3);
			}
			if (Path.IsEmpty())
			{
				CategoryId = Id;
				continue;
			}

			// Create a new NavItem and add it to the array
			FDocsPageItem NavItem;
			NavItem.Id = CategoryId + TEXT("/") + Id;
			NavItem.Path = Path;
			NavItems.Add(NavItem);

			UE_LOG(LogTemp, Log, TEXT("Parsed Nav Item - Id: %s, Path: %s"), *NavItem.Id, *NavItem.Path);
		}
	}

	// Now you have an array of NavItems you can use as needed
	// For demonstration, let's log all of them
	UE_LOG(LogTemp, Log, TEXT("Total Nav Items Parsed: %d"), NavItems.Num());
	for (const FDocsPageItem& Item : NavItems)
	{
		UE_LOG(LogTemp, Log, TEXT("Id: %s, Path: %s"), *Item.Id, *Item.Path);
	}
	GEditor->GetEditorSubsystem<UBeamEditor>()->DocsPages = NavItems;

	// Get the active BeamProj
	ActiveBeamProj = ModulesStr[0];

	// Listen for content changes and keep them in-sync
	EditorContent = GEditor->GetEditorSubsystem<UBeamEditorContent>();
	OnContentSavedHandle = EditorContent->OnContentSaved.AddUObject(this, &ThisClass::OnContentSaved);

	// Listen for realm changes and keep them in-sync	
	Editor->OnAppliedSettingsToBuild.AddUniqueDynamic(this, &ThisClass::UBeamProjSyncSubsystem::OnAppliedSettingsToBuild);
	
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
			
			if (PlatformFile.DirectoryExists(*AbsTargetDir))
				PlatformFile.DeleteDirectoryRecursively(*AbsTargetDir);

			bool bSuccess = CopyDirectoryRecursive(AbsWatchDir, AbsTargetDir);
			if (bSuccess)
			{
				UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to Sync BEAMPROJ. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
			}
			
		});

		if (IFileManager::Get().DirectoryExists(*AbsWatchDir))
		{
			DirectoryWatcher->RegisterDirectoryChangedCallback_Handle(AbsWatchDir, OnChanged, OverridenDirectoriesHandlers[i], IDirectoryWatcher::WatchOptions::IncludeDirectoryChanges);
		}
		
	}

	// Listen for undo/redo
	OnUndoRedoHandle = FEditorDelegates::PostUndoRedo.AddUObject(this, &ThisClass::OnObjectRedoUndo);
	OnPreBeginPIEHandle = FEditorDelegates::PreBeginPIE.AddUObject(this, &ThisClass::OnEnterPie);

	return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
}

void UBeamProjSyncSubsystem::Deinitialize()
{
	// Stop listening to the content system
	if (EditorContent)
		EditorContent->OnContentSaved.Remove(OnContentSavedHandle);

	// Stop listening to realm changes
	if (Editor)
		Editor->OnAppliedSettingsToBuild.RemoveDynamic(this, &ThisClass::OnAppliedSettingsToBuild);

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
	FEditorDelegates::PostUndoRedo.Remove(OnUndoRedoHandle);
	FEditorDelegates::PreBeginPIE.Remove(OnPreBeginPIEHandle);
}

void UBeamProjSyncSubsystem::OnEnterPie(bool) const
{
	SyncAllOverridenDirectories();
}

void UBeamProjSyncSubsystem::OnObjectRedoUndo() const
{
	SyncAllOverridenDirectories();
}

void UBeamProjSyncSubsystem::OnContentSaved(FBeamContentManifestId ManifestId, FBeamContentId Id)
{
	FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
	GetPaths(BeamableContentDir(), WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.CopyDirectoryTree(*AbsTargetDir, *AbsWatchDir, true))
	{
		UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Sync BEAMPROJ. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
	}
}

void UBeamProjSyncSubsystem::OnAppliedSettingsToBuild()
{
	FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
	GetPaths(UnrealConfigDir(), WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.CopyDirectoryTree(*AbsTargetDir, *AbsWatchDir, true))
	{
		UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Sync BEAMPROJ. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
	}
}

void UBeamProjSyncSubsystem::SyncAllOverridenDirectories() const
{
	for (int i = 0; i < OverridenDirectories.Num(); ++i)
	{
		const auto OverridenDirectory = OverridenDirectories[i];
		FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
		GetPaths(OverridenDirectory, WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);
		
		bool bSuccess = CopyDirectoryRecursive(WatchDir, TargetDir);
		if (bSuccess)
		{
			UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to Sync BEAMPROJ. BEAMPROJ=%s WATCH_DIR=%s, TARGET_DIR=%s"), *ActiveBeamProj, *AbsWatchDir, *AbsTargetDir);
		}
	}
}

void UBeamProjSyncSubsystem::GetPaths(const FString& OverridenDirectory, FString& WatchDir, FString& TargetDir, FString& AbsWatchDir, FString& AbsTargetDir) const
{
	WatchDir = FPaths::ProjectDir() / OverridenDirectory;
	TargetDir = FPaths::ProjectDir() / TEXT("Plugins") / ActiveBeamProj / TEXT("Overrides") / OverridenDirectory;

	AbsWatchDir = FPaths::IsRelative(WatchDir) ? FPaths::ConvertRelativePathToFull(WatchDir) : WatchDir;
	AbsTargetDir = FPaths::IsRelative(TargetDir) ? FPaths::ConvertRelativePathToFull(TargetDir) : TargetDir;
}

