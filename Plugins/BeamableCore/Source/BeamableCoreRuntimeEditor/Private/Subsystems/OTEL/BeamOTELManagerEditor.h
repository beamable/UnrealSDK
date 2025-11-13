// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "BeamOTELManagerEditor.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIMEEDITOR_API UBeamOTELManagerEditor : public UBeamEditorSubsystem
{
    GENERATED_BODY()

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
    /**
     * When we initialize the realm we push the logs.
     */
    virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

    void AddLog(FString Message, FString StackTrace, FString OtelLogLevel);

    void OtelPruneLogs();

    void PublishLogs();


    FString GetLatestCrashLogPath()
    {
        // Base crash directory
        FString CrashBaseDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Crashes"));

        // Find all crash subfolders
        TArray<FString> CrashFolders;
        IFileManager::Get().FindFiles(CrashFolders, *CrashBaseDir, false, true);

        if (CrashFolders.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No crash folders found in %s"), *CrashBaseDir);
            return FString();
        }

        // Sort by modification time (newest first)
        CrashFolders.Sort([&](const FString& A, const FString& B)
        {
            FDateTime TimeA = IFileManager::Get().GetTimeStamp(*(FPaths::Combine(CrashBaseDir, A)));
            FDateTime TimeB = IFileManager::Get().GetTimeStamp(*(FPaths::Combine(CrashBaseDir, B)));
            return TimeA > TimeB;
        });

        // Full path to the latest crash folder
        FString LatestCrashDir = FPaths::Combine(CrashBaseDir, CrashFolders[0]);

        // Look for common crash log files inside
        TArray<FString> CrashFiles;
        IFileManager::Get().FindFilesRecursive(
            CrashFiles,
            *LatestCrashDir,
            TEXT("*.*"), // get all files
            true,
            false
        );

        if (CrashFiles.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No crash files found in %s"), *LatestCrashDir);
            return FString();
        }

        // Prioritize known crash log file types
        FString FoundLogPath;
        for (const FString& FilePath : CrashFiles)
        {
            if (FilePath.EndsWith(TEXT(".log")))
            {
                FoundLogPath = FilePath;
                break;
            }
        }

        // Fallback: use the newest file if none matched
        if (FoundLogPath.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("No log file found in %s"), *LatestCrashDir);
            return FString();
        }

        UE_LOG(LogTemp, Log, TEXT("Latest crash log file: %s"), *FoundLogPath)

        return FoundLogPath;
    }

    // Check if the crash log is already flagged as used
    static bool IsCrashLogAlreadyUsed(const FString& FilePath, FString& OutFileContent)
    {
        if (!FFileHelper::LoadFileToString(OutFileContent, *FilePath))
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to read file: %s"), *FilePath);
            return false;
        }

        return OutFileContent.Contains(TEXT("UsedByCrashCollector=true"));
    }

    // Flag the crash log as used
    static bool FlagCrashLogAsUsed(const FString& FilePath)
    {
        FString Marker = TEXT("\n# FLAG: UsedByCrashCollector=true\n");

        if (FFileHelper::SaveStringToFile(Marker, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append))
        {
            UE_LOG(LogTemp, Log, TEXT("Flagged crash log as used: %s"), *FilePath);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to append flag to: %s"), *FilePath);
            return false;
        }
    }

    void CheckAndFlagLatestCrash()
    {
        FString CrashLogPath = GetLatestCrashLogPath();

        if (CrashLogPath.IsEmpty())
        {
            UE_LOG(LogTemp, Log, TEXT("No crash log found."));
            return;
        }
        FString FileContent;
        
        // If the crash is not used yet we add to logs and mark it as used.
        if (!IsCrashLogAlreadyUsed(CrashLogPath, FileContent))
        {
            AddLog(FString::Printf(TEXT("Unreal Editor Crash - Project: %s"), FApp::GetProjectName()), FileContent, "Critical");
       
            FlagCrashLogAsUsed(CrashLogPath);
        }
    }
};
