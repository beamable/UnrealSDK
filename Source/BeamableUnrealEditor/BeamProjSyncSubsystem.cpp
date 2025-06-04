// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamProjSyncSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/OutputDeviceDebug.h"

static bool ShouldIgnoreDirectory(const FString& Path)
{
	bool ShouldIgnore = false;
	TArray<FString> PathParts;
	Path.ParseIntoArray(PathParts, TEXT("/"), true);
	for (auto IgnoreDirectory : UBeamProjSyncSubsystem::IgnoreDirectories)
	{
		if (PathParts.Contains(IgnoreDirectory))
		{
			ShouldIgnore = true;
			break;
		}
	}

	return ShouldIgnore;
}


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

		// Check if any part of the relative path contains the ignore path.
		if (!ShouldIgnoreDirectory(RelativePath))
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

				if (!platformFile.CopyFile(*TargetPath, *Path, EPlatformFileRead::AllowWrite, EPlatformFileWrite::AllowRead))
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to copy file: %s , %s"), *Path, *TargetPath);
					return false;
				}
			}
		}
	}

	return true;
}


bool UBeamProjSyncSubsystem::SyncAllOverridenDirectories() const
{
	bool bSuccess = true;
	for (int i = 0; i < OverridenDirectories.Num(); ++i)
	{
		const auto OverridenDirectory = OverridenDirectories[i];
		FString WatchDir, AbsWatchDir, TargetDir, AbsTargetDir;
		GetPaths(OverridenDirectory, WatchDir, TargetDir, AbsWatchDir, AbsTargetDir);

		auto Success = CopyDirectoryRecursive(WatchDir, TargetDir);
		if (bSuccess)
		{
			UE_LOG(LogTemp, Display, TEXT("Keeping BEAMPROJ in Sync. BEAMPROJ=%s DIR=%s, TARGET_DIR=%s"), *GetActiveBeamProj(), *AbsWatchDir, *AbsTargetDir);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to Sync BEAMPROJ. BEAMPROJ=%s DIR=%s, TARGET_DIR=%s"), *GetActiveBeamProj(), *AbsWatchDir, *AbsTargetDir);
		}
		bSuccess &= Success;
	}
	return bSuccess;
}

void UBeamProjSyncSubsystem::GetPaths(const FString& OverridenDirectory, FString& WatchDir, FString& TargetDir, FString& AbsWatchDir, FString& AbsTargetDir) const
{
	WatchDir = FPaths::ProjectDir() / OverridenDirectory;
	TargetDir = FPaths::ProjectDir() / TEXT("Plugins") / GetActiveBeamProj() / TEXT("Overrides") / OverridenDirectory;

	AbsWatchDir = FPaths::IsRelative(WatchDir) ? FPaths::ConvertRelativePathToFull(WatchDir) : WatchDir;
	AbsTargetDir = FPaths::IsRelative(TargetDir) ? FPaths::ConvertRelativePathToFull(TargetDir) : TargetDir;
}

FString UBeamProjSyncSubsystem::GetActiveBeamProj() const
{
	IPluginManager& PluginManager = IPluginManager::Get();

	TArray<TSharedRef<IPlugin>> Plugins = PluginManager.GetDiscoveredPlugins();

	for (const TSharedRef<IPlugin>& Plugin : Plugins)
	{
		// Check if the plugin is enabled
		if (Plugin->GetName().StartsWith("BEAMPROJ_") && Plugin->IsEnabled())
		{
			return Plugin->GetName();
		}
	}

	return KBeamProj_Sandbox;
}

void UBeamProjSyncSubsystem::ApplyProjectOverrides(const FString& BeamProj) const
{
	TArray<FString> Overrides = {TEXT("steam_appid.txt")};
	FString ProjRoot = FPaths::ProjectDir();
	FString OverridesRoot = FPaths::Combine(ProjRoot, TEXT("Plugins"), BeamProj, TEXT("Overrides"));

	// Handling file overrides
	for (const FString& Entry : Overrides)
	{
		FString FilePath = FPaths::Combine(ProjRoot, Entry);
		if (FPaths::FileExists(FilePath))
		{
			IFileManager::Get().Delete(*FilePath); // Delete the file if it exists
		}

		FString TargetFilePath = FPaths::Combine(OverridesRoot, Entry);
		if (FPaths::FileExists(TargetFilePath))
		{
			// Copy file from the overrides root to project root
			IFileManager::Get().Copy(*FilePath, *TargetFilePath);
		}
	}

	// Handling directory overrides
	TArray<FString> OverrideFolders = {TEXT("Config"), TEXT(".beamable/content")};

	for (const FString& OverrideFolder : OverrideFolders)
	{
		FString ProjectPath = FPaths::Combine(ProjRoot, OverrideFolder);
		FString OverridesPath = FPaths::Combine(OverridesRoot, OverrideFolder);

		if (!FPaths::DirectoryExists(OverridesPath))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s project does not have Overrides directory for this expected override path. Create one at: %s"), *BeamProj, *OverridesPath);
			return;
		}

		if (FPaths::DirectoryExists(ProjectPath))
		{
			// Delete existing directory (recursive)
			IFileManager::Get().DeleteDirectory(*ProjectPath, false, true);
		}

		// Copy directory contents
		CopyDirectory(OverridesPath, ProjectPath);
	}
}

void UBeamProjSyncSubsystem::CopyDirectory(const FString& SourceDir, const FString& DestinationDir) const
{
	// Check if the source directory exists
	if (!FPaths::DirectoryExists(SourceDir))
	{
		return;
	}

	// Create the destination directory if it doesn't exist
	IFileManager::Get().MakeDirectory(*DestinationDir, true);

	// Get all files in the source directory
	TArray<FString> FileNames;
	IFileManager::Get().FindFiles(FileNames, *SourceDir, TEXT("*"));

	// Copy each file from source to destination
	for (const FString& File : FileNames)
	{
		FString SourceFile = FPaths::Combine(SourceDir, File);
		FString DestinationFile = FPaths::Combine(DestinationDir, File);
		IFileManager::Get().Copy(*DestinationFile, *SourceFile);
	}

	// Get all subdirectories in the source directory
	TArray<FString> SubDirs;
	IFileManager::Get().FindFiles(SubDirs, *SourceDir, TEXT("*"));

	for (const FString& SubDir : SubDirs)
	{
		FString NewSourceDir = FPaths::Combine(SourceDir, SubDir);
		FString NewDestinationDir = FPaths::Combine(DestinationDir, SubDir);
		CopyDirectory(NewSourceDir, NewDestinationDir); // Recursively copy subdirectories
	}
}
