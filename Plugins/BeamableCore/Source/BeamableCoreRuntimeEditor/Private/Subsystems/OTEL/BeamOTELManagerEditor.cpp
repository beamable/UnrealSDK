// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamOTELManagerEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliTelemetryPruneCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliTelemetryPushCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliTelemetryReportCommand.h"

void UBeamOTELManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UnrealOtelLogsFolder = FPaths::Combine(FPaths::EngineSavedDir(), TEXT("Beamable"), TEXT("BeamableOtelLogs"));
	
	UE_LOG(LogTemp, Warning, TEXT("PATH TO TEMP: %s"), *UnrealOtelLogsFolder);
}

FBeamOperationHandle UBeamOTELManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	// Just fire and forget the command push
	OtelPublishLogs();
	
	return Super::OnRealmInitialized(NewRealm);
}

void UBeamOTELManagerEditor::OtelAddLog(FString Message, FString StackTrace, FString OtelLogLevel)
{
	// 1. Generate hash key
	FString HashCode = GetLogKey(
		Message,
		StackTrace,
		OtelLogLevel,
		nullptr,
		nullptr
	);

	// 2. Generate timestamp (ISO-8601 UTC)
	FString Timestamp = FDateTime::UtcNow().ToIso8601();

	// 3. Add CliOtelLogRecord to CachedLogs (equivalent of TryAdd)
	if (!CachedLogs.Contains(HashCode))
	{
		FCliOtelLogRecord Record;
		Record.Timestamp = Timestamp;
		Record.LogLevel = OtelLogLevel;
		Record.Body = FString::Printf(TEXT("LogMessage: %s\nStacktrace: %s"), *Message, *StackTrace);
		Record.ExceptionMessage = TEXT("");
		Record.ExceptionStackTrace = TEXT("");
		Record.Attributes = TMap<FString, FString>();

		CachedLogs.Add(HashCode, Record);
	}

	// 4. Maintain timestamp list (equivalent to TryGetValue + List.Add)
	TArray<FString>* Timestamps = CachedTimestamps.Find(HashCode);
	if (!Timestamps)
	{
		CachedTimestamps.Add(HashCode, TArray<FString>());
		Timestamps = CachedTimestamps.Find(HashCode);
	}

	Timestamps->Add(Timestamp);
}

void UBeamOTELManagerEditor::OtelPruneLogs()
{
	UBeamCliTelemetryPruneCommand* PruneCommand = NewObject<UBeamCliTelemetryPruneCommand>();
	
	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	
	Cli->RunCommand(PruneCommand, {TEXT("--delete-all"), TEXT("-q")}, {});
}

void UBeamOTELManagerEditor::OtelPublishLogs()
{
	FlushUnrealLogs();

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (!PlatformFile.DirectoryExists(*UnrealOtelLogsFolder))
	{
		return;
	}
	
	TArray<FString> AllFiles;
	PlatformFile.FindFiles(AllFiles, *UnrealOtelLogsFolder, nullptr);

	if (AllFiles.Num() == 0)
	{
		return;
	}

	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();

	TArray<FString> GenBeamCommandArgs;
	
	if (AllFiles.Num() > 0)
	{
		for (const FString& Path : AllFiles)
		{
			GenBeamCommandArgs.Add(TEXT("--paths=") + Path);
		}
	}
	
	UBeamCliTelemetryReportCommand* ReportCommand = NewObject<UBeamCliTelemetryReportCommand>();

	ReportCommand->OnStreamOutput = [Cli](TArray<UBeamCliTelemetryReportStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)
	{
		for (auto ReportItem : StreamData[0]->AllStatus)
		{
			if (ReportItem->Success)
			{
				if (FPaths::FileExists(ReportItem->FilePath))
				{
					IFileManager::Get().Delete(*ReportItem->FilePath);
				}
			}
		}

		UBeamCliTelemetryPushCommand* PushCommand = NewObject<UBeamCliTelemetryPushCommand>();
			
		Cli->RunCommand(PushCommand, {TEXT("-q")}, {});
	};
	ReportCommand->OnCompleted = [](const int& ResCode, const FBeamOperationHandle& Op)
	{
		UE_LOG(LogTemp, Display, TEXT("Completed stream output"));
	};
	FString Paths;

	// Join all args with spaces
	Paths = FString::Join(GenBeamCommandArgs, TEXT(" "));
	
	Cli->RunCommand(ReportCommand, {Paths, TEXT("-q")}, {});
	
}





