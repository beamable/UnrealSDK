// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/CLI/Autogen/StreamData/CollectorStatusStreamData.h"
#include "BeamOTELManagerEditor.generated.h"


USTRUCT(BlueprintType)
struct FCliOtelLogRecord
{
    GENERATED_BODY()

public:

    // Timestamp as string (can be converted to FDateTime if needed)
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Timestamp;

    // Log level kept as string exactly like C#
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString LogLevel;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Body;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ExceptionMessage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ExceptionStackTrace;

    // Dictionary<string, string> equivalent
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FString> Attributes;
};

USTRUCT(BlueprintType)
struct FCliOtelMessage
{
    GENERATED_BODY()

public:

    // Array of log records
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCliOtelLogRecord> AllLogs;
};



/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIMEEDITOR_API UBeamOTELManagerEditor : public UBeamEditorSubsystem
{
    GENERATED_BODY()
    const float ReportTelemetryDelay = 120;
    
    FString UnrealOtelLogsFolder;
    
    FTSTicker::FDelegateHandle TickerHandle;
    
    TMap<FString, FCliOtelLogRecord> CachedLogs;
    TMap<FString, TArray<FString>> CachedTimestamps;
    
    float TimeAccumulated = 0;
    UCollectorStatusStreamData* CollectorStatus;

protected:
    
    
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // This is called every minute
    bool ReportOtelLogsEachMinute(float DeltaTime);
    
public:
    /**
     * When we initialize the realm we push the logs.
     */
    virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

    

    void OtelAddLog(FString Message, FString StackTrace, FString OtelLogLevel);

    void OtelPruneLogs();

    void OtelReportLogs();

    void OtelPublishLogs();

    void StartCollectorPs(FBeamOperationHandle Op);

    bool ParseUnrealLogs(FString& FileName, FString& JsonData)
    {
        // Early exit if logs empty
        if (CachedLogs.Num() == 0)
        {
            return false;
        }

        // Ensure folder exists
        IFileManager::Get().MakeDirectory(*UnrealOtelLogsFolder, true);

        // Build grouped logs
        TArray<FCliOtelLogRecord> GroupedLogs;
        GroupedLogs.Reserve(CachedLogs.Num());

        for (const TPair<FString, FCliOtelLogRecord>& Pair : CachedLogs)
        {
            const FString& HashKey = Pair.Key;
            FCliOtelLogRecord LogData = Pair.Value;

            // Ensure Attributes exists
            if (LogData.Attributes.Num() == 0)
            {
                LogData.Attributes = TMap<FString, FString>();
            }

            // Add timestamps as JSON array inside a string (same behavior as C#)
            const TArray<FString>* Timestamps = CachedTimestamps.Find(HashKey);
            if (Timestamps)
            {
                FString Joined = TEXT("[") + FString::Join(*Timestamps, TEXT(", ")) + TEXT("]");
                LogData.Attributes.Add("x-beam-extra-timestamps", Joined);
            }

            GroupedLogs.Add(LogData);
        }

        // Clear caches like C#
        CachedLogs.Empty();
        CachedTimestamps.Empty();

        // Construct the message wrapper struct
        FCliOtelMessage Message;
        Message.AllLogs = GroupedLogs;

        // Serialize to JSON
        FString JsonOutput;
        FJsonObjectConverter::UStructToJsonObjectString(Message, JsonOutput);

        JsonData = JsonOutput;

        // Filename: UnrealOtelLog-<unix_timestamp>.json
        int64 UnixTime = FDateTime::UtcNow().ToUnixTimestamp();
        FileName = FString::Printf(TEXT("UnrealOtelLog-%lld.json"), UnixTime);

        return true;
    }
    
    FString GetLatestCrashLogPath()
    {
        // Base crash directory
        FString CrashBaseDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Crashes"));

        // Find all crash subfolders
        TArray<FString> CrashFolders;
        IFileManager::Get().FindFiles(CrashFolders, *FPaths::Combine(CrashBaseDir, TEXT("*")), false, true);

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
            OtelAddLog(FString::Printf(TEXT("Unreal Editor Crash - Project: %s"), FApp::GetProjectName()), FileContent, "Critical");
       
            FlagCrashLogAsUsed(CrashLogPath);
        }
    }

    void FlushUnrealLogs()
    {
        FString FileName;
        FString JsonData;
        if (!ParseUnrealLogs(FileName, JsonData) || FileName.IsEmpty() || JsonData.IsEmpty())
        {
            return;
        }
        
        FString FilePath = FPaths::Combine(UnrealOtelLogsFolder, FileName);

        FFileHelper::SaveStringToFile(JsonData, *FilePath);
    }

    static FString GetLogKey(
        const FString& Message,
        const FString& StackTrace,
        const FString& OtelLogLevel,
        const FString* Exception = nullptr,
        const TMap<FString, FString>* Attributes = nullptr
        ){
        FString Combined = FString::Printf(TEXT("%s|%s|%s"),
            *Message,
            *StackTrace,
            *OtelLogLevel
        );

        // Add attributes in sorted order (by key)
        if (Attributes && Attributes->Num() > 0)
        {
            TArray<FString> Keys;
            Attributes->GetKeys(Keys);
            Keys.Sort();

            for (const FString& Key : Keys)
            {
                const FString* Value = Attributes->Find(Key);
                if (Value)
                {
                    Combined += TEXT("|") + Key + TEXT("=") + *Value;
                }
            }
        }

        // Add exception
        if (Exception)
        {
            Combined += TEXT("|") + *Exception;
        }

        return GenerateHash(Combined);
    }

    static FString GenerateHash(const FString& Input){
        if (Input.IsEmpty())
        {
            return TEXT("");
        }

        // Convert string to UTF-8 bytes
        FTCHARToUTF8 Converter(*Input);
        const uint8* Bytes = reinterpret_cast<const uint8*>(Converter.Get());
        int32 Length = Converter.Length();

        // Compute MD5
        FMD5 Md5;
        Md5.Update(Bytes, Length);

        uint8 Digest[16];
        Md5.Final(Digest);

        // Convert to lowercase hex string (same as .NET)
        FString Hash;
        for (int i = 0; i < 16; i++)
        {
            Hash += FString::Printf(TEXT("%02x"), Digest[i]);
        }

        return Hash;
    }
};
