#pragma once

#include "CoreMinimal.h"
#include "BeamCli.h"
#include "Misc/MonitoredProcess.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "Async/Async.h"
#include "BeamCliCommand.generated.h"

class FMonitoredProcess;
class UBeamCli;
class UBeamEditor;
class UBeamRequestTracker;

UCLASS(Abstract)
class UBeamCliCommand : public UObject
{
	GENERATED_BODY()

protected:
	TSharedPtr<FMonitoredProcess> CmdProcess;

public:
	UBeamCliCommand() = default;

	virtual void Run(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {})
	{
		RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
		Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
		Cli = GEditor->GetEditorSubsystem<UBeamCli>();

		checkf(Cli->IsInstalled(), TEXT("The Beamable CLI must be installed for any CLI commands to be run."))
		
		CmdProcess = RunImpl(CommandParams, Op);
		CmdProcess->Launch();
	};

	virtual void RunSync(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {})
	{
		RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
		Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
		Cli = GEditor->GetEditorSubsystem<UBeamCli>();

		checkf(Cli->IsInstalled(), TEXT("The Beamable CLI must be installed for any CLI commands to be run."))
		
		CmdProcess = RunImpl(CommandParams, Op);
		CmdProcess->Launch();

		// Busy wait until this finishes.
		while (CmdProcess->Update())
		{
		}
	}

	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams,
	                                              const FBeamOperationHandle& Op = {})
	{
		return nullptr;
	};

	const static FString PathToCli;

	const static FString Pattern;
	const static FString PatternStart;
	const static FString PatternEnd;

	bool bIsReceivingMessage;
	FString MessageBuffer;

	bool IsDone() const
	{
		return CmdProcess->Update();
	}


	bool ConsumeMessageFromOutput(FString& StdOutCopy, FString& OutMessageJson)
	{
		const auto StreamStartIdx = StdOutCopy.Find(PatternStart);
		const auto MessageStartIdx = StreamStartIdx >= 0 ? StreamStartIdx + PatternStart.Len() : StreamStartIdx;
		const auto MessageEndIdx = StdOutCopy.Find(PatternEnd);


		// Didn't see a message 
		if (!bIsReceivingMessage && (MessageStartIdx == INDEX_NONE && MessageEndIdx == INDEX_NONE))
		{
			MessageBuffer = TEXT("");
			return false;
		}

		// If we are not receiving a message and we receive a full one in a single StdOut call, we parse it out and  
		if (!bIsReceivingMessage && MessageStartIdx != INDEX_NONE && MessageEndIdx != INDEX_NONE)
		{
			OutMessageJson = StdOutCopy.RightChop(StreamStartIdx + PatternStart.Len()).LeftChop(PatternEnd.Len());
			StdOutCopy = StdOutCopy.RightChop(MessageEndIdx + PatternEnd.Len());			
			// This means a message was completely received and is ready to be sent.
			return true;
		}

		// If we are not receiving a message and we see a start but not an end, we get the start of the message into the buffer and turn on the partial message flag.
		if (!bIsReceivingMessage && (MessageStartIdx != INDEX_NONE && MessageEndIdx == INDEX_NONE))
		{
			const auto PartialMessage = StdOutCopy.RightChop(MessageStartIdx);
			bIsReceivingMessage = true;
			MessageBuffer = MessageBuffer.Append(PartialMessage);
			UE_LOG(LogTemp, Warning, TEXT("Beginning => %s"), *MessageBuffer);
			return false;
		}

		// If we are receiving a message and it wasn't finished this StdOut message; we just append the contents to the message.
		if (bIsReceivingMessage && (MessageStartIdx == INDEX_NONE && MessageEndIdx == INDEX_NONE))
		{
			MessageBuffer = MessageBuffer.Append(StdOutCopy);
			return false;
		}

		// If we are receiving a message and it was finished in this StdOut message; we append this to 
		if (bIsReceivingMessage && (MessageStartIdx == INDEX_NONE && MessageEndIdx != INDEX_NONE))
		{
			const auto PartialMessage = StdOutCopy.Mid(0, MessageEndIdx);
			bIsReceivingMessage = false;
			MessageBuffer = MessageBuffer.Append(PartialMessage);
			OutMessageJson = MessageBuffer;
			UE_LOG(LogTemp, Warning, TEXT("Ending => %s"), *MessageBuffer);
			MessageBuffer = TEXT("");
			// This means a message was completely received and is ready to be sent.
			return true;
		}

		return false;
	}


	static FString PrepareParams(FString Params)
	{
		return Params.Append(" --reporter-use-fatal");
	}

protected:
	UBeamRequestTracker* RequestTracker;
	UBeamEditor* Editor;
	UBeamCli* Cli;
};


inline const FString UBeamCliCommand::PathToCli = FString(TEXT("beam"));
inline const FString UBeamCliCommand::Pattern = FString(TEXT("__@#!REPORT!#@__"));
inline const FString UBeamCliCommand::PatternStart = FString(TEXT("<__@#!REPORT!#@__>"));
inline const FString UBeamCliCommand::PatternEnd = FString(TEXT("</__@#!REPORT!#@__>"));
