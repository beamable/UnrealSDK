#include "Subsystems/CLI/BeamCliCommand.h"

const FString UBeamCliCommand::PathToLocalCli = FString(TEXT("dotnet"));

FString UBeamCliCommand::PrepareParams(FString Params)
{
	return Params.Append(" -q");
}

void UBeamCliCommand::Run(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();

	checkf(Cli->IsInstalled(), TEXT("The Beamable CLI must be installed for any CLI commands to be run."))

	PrepareCommandProcess(CommandParams, Op);
	CmdProcess->Launch();
}

void UBeamCliCommand::RunSync(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	Run(CommandParams, Op);
	
	// Busy wait until this finishes.
	while (CmdProcess->Update())
	{
	}
}

void UBeamCliCommand::RunServer(const FString Uri, const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();

	checkf(Cli->IsInstalled(), TEXT("The Beamable CLI must be installed for any CLI commands to be run."))

	FString CommandLineToExecute = GetCommand();
	for (const auto& CommandParam : CommandParams)
		CommandLineToExecute.Appendf(TEXT(" %s"), *CommandParam);

	CommandLineToExecute = PrepareParams(CommandLineToExecute);

	FJsonDomBuilder::FObject Obj;
	Obj.Set(TEXT("commandLine"), CommandLineToExecute);

	const auto ReqContent = Obj.ToString();
	CmdRequest = FHttpModule::Get().CreateRequest().ToSharedPtr();
	CmdRequest->SetVerb("POST");
	CmdRequest->SetURL(Uri / TEXT("execute"));
	CmdRequest->SetContentAsString(ReqContent);
	CmdRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	CmdRequest->OnProcessRequestComplete().BindLambda([this, Op, CommandLineToExecute](TSharedPtr<IHttpRequest>, TSharedPtr<IHttpResponse> HttpResponse, bool)
	{
		const auto RespCode = HttpResponse->GetResponseCode();
		if (RespCode >= 200 && RespCode < 300)
		{
			auto MessageJson = HttpResponse->GetContentAsString();
			MessageJson.RemoveAt(0, FString(TEXT("data: ")).Len());
			
			UE_LOG(LogBeamCli, Display, TEXT("BeamCli Server - Executed command. CMD=%s, RESPONSE=%s"), *CommandLineToExecute, *MessageJson);
			
			auto Bag = FJsonDataBag();
			if (Bag.FromJson(MessageJson))
			{
				UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Server - Processing JSON message. CMD=%s, JSON=%s"), *CommandLineToExecute, *MessageJson);

				const auto ReceivedStreamType = Bag.GetString(TEXT("type"));
				const auto Timestamp = static_cast<int64>(Bag.GetField(TEXT("ts"))->AsNumber());
				const auto DataJson = Bag.JsonObject->GetObjectField(TEXT("data")).ToSharedRef();

				HandleStreamReceived(Op, ReceivedStreamType, Timestamp, DataJson, true);
				HandleStreamCompleted(Op, 0, true);
			}
			else
			{
				UE_LOG(LogBeamCli, Warning, TEXT("BeamCli Server - Ignoring non-JSON message. CMD=%s, JSON=%s"), *CommandLineToExecute, *MessageJson);
			}
		}
		else
		{
			UE_LOG(LogBeamCli, Error, TEXT("BeamCli Server - Error in executing command. CMD=%s, RESPONSE=%s"), *CommandLineToExecute, *HttpResponse->GetContentAsString());
			HandleStreamCompleted(Op, 1, true);
		}
	});

	CmdRequest->ProcessRequest();	
}

void UBeamCliCommand::PrepareCommandProcess(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();

	checkf(Cli->IsInstalled(), TEXT("The Beamable CLI must be installed for any CLI commands to be run."))

	FString Params = TEXT("beam ") + GetCommand();
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Command Invocation: %s %s"), *PathToLocalCli, *Params)

	const auto CliPath = Cli->GetPathToCli();
	CmdProcess = MakeShared<FMonitoredProcess>(CliPath, Params, FPaths::ProjectDir(), true, true);
	CmdProcess->OnOutput().BindLambda([this, Op, Params](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Command - Std Out: %s"), *Out);
		FString OutCopy = Out;
		FString MessageJson;
		while (ConsumeMessageFromOutput(OutCopy, MessageJson))
		{
			auto Bag = FJsonDataBag();
			if (Bag.FromJson(MessageJson))
			{
				UE_LOG(LogBeamCli, Display, TEXT("BeamCli Command - Message Received. CMD=%s, MESSAGE=%s"), *Params, *MessageJson);

				const auto ReceivedStreamType = Bag.GetString(TEXT("type"));
				const auto Timestamp = static_cast<int64>(Bag.GetField(TEXT("ts"))->AsNumber());
				const auto DataJson = Bag.JsonObject->GetObjectField(TEXT("data")).ToSharedRef();

				HandleStreamReceived(Op, ReceivedStreamType, Timestamp, DataJson, false);
			}
			else
			{
				UE_LOG(LogBeamCli, Warning, TEXT("BeamCli Command - Skipping non-JSON message. CMD=%s, MESSAGE=%s"), *Params, *MessageJson);
			}
		}
	});
	CmdProcess->OnCompleted().BindLambda([this, Op](int ResultCode)
	{
		HandleStreamCompleted(Op, ResultCode, false);
	});
}

bool UBeamCliCommand::IsDone() const
{
	if(CmdProcess.IsValid())
		return CmdProcess->Update();

	if(CmdRequest.IsValid())
		return CmdRequest->GetStatus() != EHttpRequestStatus::NotStarted && CmdRequest->GetStatus() != EHttpRequestStatus::Processing;

	return false;
}

bool UBeamCliCommand::ConsumeMessageFromOutput(FString& StdOutCopy, FString& OutMessageJson)
{
	const auto StreamStartIdx = 0;
	const auto MessageStartIdx = 0;
	const auto MessageEndIdx = StdOutCopy.Len();

	// If there's nothing in the buffer, we just skip out.
	if (StdOutCopy.IsEmpty())
		return false;

	// If we are not receiving a message and we receive a full one in a single StdOut call, we parse it out and  
	if (!bIsReceivingMessage && MessageEndIdx != INDEX_NONE)
	{
		OutMessageJson = StdOutCopy.RightChop(StreamStartIdx);
		StdOutCopy = StdOutCopy.RightChop(MessageEndIdx);
		// This means a message was completely received and is ready to be sent.
		return true;
	}

	// If we are not receiving a message and we see a start but not an end, we get the start of the message into the buffer and turn on the partial message flag.
	if (!bIsReceivingMessage && (MessageEndIdx == INDEX_NONE))
	{
		const auto PartialMessage = StdOutCopy.RightChop(MessageStartIdx);
		bIsReceivingMessage = true;
		MessageBuffer = MessageBuffer.Append(PartialMessage);
		UE_LOG(LogTemp, Warning, TEXT("Beginning => %s"), *MessageBuffer);
		return false;
	}

	return false;
}

FString UBeamCliCommand::GetCommand()
{
	return TEXT("");
}

void UBeamCliCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
}

void UBeamCliCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
}
