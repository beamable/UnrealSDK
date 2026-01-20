// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamOTELManagerEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliTelemetryCollectorPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliTelemetryPruneCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliTelemetryPushCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliTelemetryReportCommand.h"

void UBeamOTELManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UnrealOtelLogsFolder = FPaths::Combine(FPaths::EngineSavedDir(), TEXT("Beamable"), TEXT("BeamableOtelLogs"));
	
	FBeamLogging::BeamLoggingMessageHook.AddUObject(this, &UBeamOTELManagerEditor::OtelAddLog);

}

void UBeamOTELManagerEditor::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
	Super::Deinitialize();
}

bool UBeamOTELManagerEditor::ReportOtelLogsEachMinute(float DeltaTime)
{
	TimeAccumulated += DeltaTime;

	if (TimeAccumulated >= ReportTelemetryDelay)
	{
		TimeAccumulated = 0.f;

		OtelReportLogs();
	}
	return true; 
}

FBeamOperationHandle UBeamOTELManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	// Just fire and forget the command push
	// OtelPublishLogs();
	const FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	StartCollectorPs(Op);
	
	return Op;
}

void UBeamOTELManagerEditor::OtelAddLog(FString Message, FString StackTrace, FString OtelLogLevel)
{
	// Generate hash key
	FString HashCode = GetLogKey(
		Message,
		StackTrace,
		OtelLogLevel,
		nullptr,
		nullptr
	);
	
	FString Timestamp = FDateTime::UtcNow().ToIso8601();

	// Add CliOtelLogRecord to CachedLogs (equivalent of TryAdd)
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

	// Maintain timestamp list (equivalent to TryGetValue + List.Add)
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

void UBeamOTELManagerEditor::OtelReportLogs()
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
			GenBeamCommandArgs.Add(FString::Printf(TEXT("--paths=\"%s\""), *Path));
		}
	}

	FString Engine = FString::Printf(TEXT("--engine %s"), TEXT("\"unreal\""));
		
	FString EngineVersion = FString::Printf(TEXT("--engine-version \"unreal-%d.%d.%d\""), ENGINE_MAJOR_VERSION, ENGINE_MINOR_VERSION, ENGINE_PATCH_VERSION);
		
	FString SdkVersion = FString::Printf(TEXT("--engine-sdk-version \"%s\""), *GetDefault<UBeamCoreSettings>()->BeamableInfoData->Version.ToString());
	
	UBeamCliTelemetryReportCommand* ReportCommand = NewObject<UBeamCliTelemetryReportCommand>();

	ReportCommand->OnStreamOutput = [](TArray<UBeamCliTelemetryReportStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)
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

	
	};
	ReportCommand->OnCompleted = [](const int& ResCode, const FBeamOperationHandle& Op)
	{

	};
	FString Paths;

	// Join all args with spaces
	Paths = FString::Join(GenBeamCommandArgs, TEXT(" "));
	
	Cli->RunCommandSync(ReportCommand, {Paths, Engine, EngineVersion, SdkVersion, TEXT("-q")});
}

void UBeamOTELManagerEditor::OtelPublishLogs()
{
	if (CollectorStatus == nullptr || !CollectorStatus->IsReady || !CollectorStatus->IsRunning)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to publish otel logs but collector wans't running or ready."));
		return;
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("Publishing Otel logs."));
	}
	FString Engine = FString::Printf(TEXT("--engine %s"), TEXT("\"unreal\""));
		
	FString EngineVersion = FString::Printf(TEXT("--engine-version \"unreal-%d.%d.%d\""), ENGINE_MAJOR_VERSION, ENGINE_MINOR_VERSION, ENGINE_PATCH_VERSION);
		
	FString SdkVersion = FString::Printf(TEXT("--engine-sdk-version \"%s\""), *GetDefault<UBeamCoreSettings>()->BeamableInfoData.LoadSynchronous()->Version.ToString());
	
	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	
	UBeamCliTelemetryPushCommand* PushCommand = NewObject<UBeamCliTelemetryPushCommand>();
		
	Cli->RunCommand(PushCommand, {Engine, EngineVersion, SdkVersion, TEXT("-q")}, {});
	
}

void UBeamOTELManagerEditor::StartCollectorPs(FBeamOperationHandle Op)
{
	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	
	auto WatchCommand = NewObject<UBeamCliTelemetryCollectorPsCommand>();

	WatchCommand->bShowReceivedMessageDebug = false;
	
	WatchCommand->OnStreamOutput = [this](TArray<UBeamCliTelemetryCollectorPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		if (Stream.Num() > 0 && Stream.Last()->CollectorsStatus.Num() > 0)
		{
			// If receive the collector status a it is runn
			bool bShouldStartOtelRoutine = CollectorStatus == nullptr;
			
			CollectorStatus = Stream.Last()->CollectorsStatus.Last();
			
			if (bShouldStartOtelRoutine)
			{
				OtelPublishLogs();
				
				TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
				  FTickerDelegate::CreateUObject(this, &UBeamOTELManagerEditor::ReportOtelLogsEachMinute),
				  0.1f
				);
			}
		}
		
	};

	WatchCommand->OnExtraStreamStreamOutput = [this](TArray<UBeamCliTelemetryCollectorPsExtraStreamStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		
		
	};
	WatchCommand->OnCompleted = [this, Cli, WatchCommand](const int& ResCode, const FBeamOperationHandle&)
	{
	};

	Cli->RunCommand(WatchCommand, {}, {});
}





