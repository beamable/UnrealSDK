#include "Subsystems/CLI/BeamCliCommand.h"

#include "JsonDomBuilder.h"
#include "Interfaces/IHttpResponse.h"


void UBeamCliLogEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("logLevel"), LogLevel);
	Serializer->WriteValue(TEXT("message"), Message);
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
}

void UBeamCliLogEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("logLevel"), LogLevel);
	Serializer->WriteValue(TEXT("message"), Message);
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
}

void UBeamCliLogEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LogLevel = Bag->GetStringField(TEXT("logLevel"));
	Message = Bag->GetStringField(TEXT("message"));
	Timestamp = Bag->GetIntegerField(TEXT("timestamp"));
}

void FBeamCliError::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("message"), Message);
	Serializer->WriteValue(TEXT("invocation"), Invocation);
	Serializer->WriteValue(TEXT("exitCode"), ExitCode);
	Serializer->WriteValue(TEXT("typeName"), TypeName);
	Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
	Serializer->WriteValue(TEXT("stackTrace"), StackTrace);
}

void FBeamCliError::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("message"), Message);
	Serializer->WriteValue(TEXT("invocation"), Invocation);
	Serializer->WriteValue(TEXT("exitCode"), ExitCode);
	Serializer->WriteValue(TEXT("typeName"), TypeName);
	Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
	Serializer->WriteValue(TEXT("stackTrace"), StackTrace);
}

void FBeamCliError::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Message = Bag->GetStringField(TEXT("message"));
	Invocation = Bag->GetStringField(TEXT("invocation"));
	ExitCode = Bag->GetIntegerField(TEXT("exitCode"));
	TypeName = Bag->GetStringField(TEXT("typeName"));
	FullTypeName = Bag->GetStringField(TEXT("fullTypeName"));
	StackTrace = Bag->GetStringField(TEXT("stackTrace"));
}

FString UBeamCliCommand::GetDotnetPath()
{
	const auto& path  = GetDefault<UBeamEditorSettings>()->DotnetExecutablePath;
	if (path.IsEmpty())
	{
#if PLATFORM_MAC
		return TEXT("/usr/local/share/dotnet/dotnet");
#else
		return TEXT("dotnet");
#endif
	}
	return path;
}

FString UBeamCliCommand::PrepareParams(FString Params)
{
	return Params.Append(" -q");
}

void UBeamCliCommand::Run(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();

	if (Cli->IsInstalled())
	{
		PrepareCommandProcess(CommandParams, Op);
		CmdProcess->Launch();
	}
	else
	{
		UE_LOG(LogBeamCli, Error, TEXT("The Beamable CLI must be installed for any CLI commands to be run. CMD=%s"), *GetCommand());
	}
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

	if (!Cli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("The Beamable CLI must be installed for any CLI commands to be run. CMD=%s"), *GetCommand());
		return;
	}

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

	CmdRequest->OnRequestProgress64().BindLambda([this, Op, CommandLineToExecute](TSharedPtr<IHttpRequest> HttpRequest, int64, int64 BytesReceived)
	{
		const auto HttpResponse = HttpRequest->GetResponse();
		if (HttpResponse.IsValid())
		{
			auto PotentialMessages = HttpResponse->GetContentAsString();
			PotentialMessages.ReplaceInline(TEXT("\u200b"),TEXT(""));

			// We process all the message but... we hash them to make sure we haven't processed them already...
			TArray<FString> PotentialJsons;
			const auto Messages = PotentialMessages.ParseIntoArrayLines(PotentialJsons);
			for (auto i = 0; i < Messages; i++)
			{
				auto Json = PotentialJsons[i];
				Json.RemoveFromStart(TEXT("data: "));

				UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Server - Processing JSON message. CMD=%s, JSON=%s"), *CommandLineToExecute, *Json);
				auto Bag = FJsonDataBag();
				if (!ProcessedMessageIndices.Contains(i))
				{
					if (Bag.FromJson(Json))
					{
						ProcessedMessageIndices.Add(i);
						UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Server - Processing JSON message. CMD=%s, JSON=%s"), *CommandLineToExecute, *Json);

						const auto ReceivedStreamType = Bag.GetString(TEXT("type"));
						const auto Timestamp = static_cast<int64>(Bag.GetField(TEXT("ts"))->AsNumber());
						const auto DataJson = Bag.JsonObject->GetObjectField(TEXT("data")).ToSharedRef();

						// If the command itself handles the data, we don't fall back to these other handlings  
						if (!HandleStreamReceived(Op, ReceivedStreamType, Timestamp, DataJson, true))
						{
							if (ReceivedStreamType.Equals(TEXT("logs")))
							{
								UBeamCliLogEntry* Data = NewObject<UBeamCliLogEntry>();
								Data->OuterOwner = this;
								Data->BeamDeserializeProperties(DataJson);

								LogEntries.Add(Data);
								LogEntriesTimestamps.Add(Timestamp);

								if (OnLogEntriesStreamOutput)
								{
									AsyncTask(ENamedThreads::GameThread, [this, Data, Timestamp, Op]
									{
										OnLogEntriesStreamOutput(Data, Timestamp, Op);
									});
								}
							}
							else if (ReceivedStreamType.StartsWith(TEXT("error")))
							{
								FBeamCliError Data = FBeamCliError{};
								Data.OuterOwner = this;
								Data.BeamDeserializeProperties(DataJson);

								Errors.Add(Data);
								ErrorsTimestamps.Add(Timestamp);

								if (OnErrorsStreamOutput)
								{
									AsyncTask(ENamedThreads::GameThread, [this, Op]
									{
										OnErrorsStreamOutput(Errors, ErrorsTimestamps, Op);
									});
								}
							}
						}
					}
					else
					{
						UE_LOG(LogBeamCli, Warning, TEXT("BeamCli Server - Ignoring non-JSON message. CMD=%s, JSON=%s"), *CommandLineToExecute, *Json);
					}
				}
			}
		}
	});
	CmdRequest->OnProcessRequestComplete().BindLambda([this, Op, CommandLineToExecute](TSharedPtr<IHttpRequest> Req, TSharedPtr<IHttpResponse> Resp, bool)
	{
		if (!Resp.IsValid())
		{
			UE_LOG(LogBeamCli, Error, TEXT("BeamCli Server - Unexpected error in executing command. CMD=%s"), *CommandLineToExecute);
			HandleStreamCompleted(Op, 999, true);
			this->Cli->OnCommandCompleted(this);
			return;
		}

		if (Errors.Num() > 0)
		{
			UE_LOG(LogBeamCli, Error, TEXT("BeamCli Server - Error in executing command. CMD=%s, ERR_CODE=%d"), *CommandLineToExecute, Errors[0].ExitCode);
			HandleStreamCompleted(Op, Errors[0].ExitCode, true);
			this->Cli->OnCommandCompleted(this);
			return;
		}

		const auto RespCode = Resp->GetResponseCode();
		if (RespCode >= 200 && RespCode < 300)
		{
			auto AllMessages = Resp->GetContentAsString();
			AllMessages.TrimEndInline();

			HandleStreamCompleted(Op, 0, true);
			UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Server - Executed command. CMD=%s, ALL_MESSAGES=%s"), *CommandLineToExecute, *AllMessages);
			this->Cli->OnCommandCompleted(this);
			return;
		}

		UE_LOG(LogBeamCli, Error, TEXT("BeamCli Server - Error in executing command. CMD=%s, ALL_MESSAGES=%s"), *CommandLineToExecute, *Resp->GetContentAsString());
		HandleStreamCompleted(Op, 500, true);
		this->Cli->OnCommandCompleted(this);
		return;
	});

	CmdRequest->ProcessRequest();
}

void UBeamCliCommand::Stop()
{
	if (CmdProcess)
	{
		CmdProcess->Stop();
	}

	if (CmdRequest)
	{
		CmdRequest->CancelRequest();
	}
}

void UBeamCliCommand::PrepareCommandProcess(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	Editor = GEditor->GetEditorSubsystem<UBeamEditor>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	const auto& path = GetDotnetPath();

	if (!Cli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("The Beamable CLI must be installed for any CLI commands to be run. CMD=%s"), *GetCommand());
		return;
	}

	FString Params = TEXT("beam ") + GetCommand();
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCli Command Invocation: %s %s"), *path, *Params)

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

				if (!HandleStreamReceived(Op, ReceivedStreamType, Timestamp, DataJson, false))
				{
					if (ReceivedStreamType.Equals(TEXT("logs")))
					{
						UBeamCliLogEntry* Data = NewObject<UBeamCliLogEntry>();
						Data->OuterOwner = this;
						Data->BeamDeserializeProperties(DataJson);

						LogEntries.Add(Data);
						LogEntriesTimestamps.Add(Timestamp);

						if (OnLogEntriesStreamOutput)
						{
							AsyncTask(ENamedThreads::GameThread, [this, Data, Timestamp, Op]
							{
								OnLogEntriesStreamOutput(Data, Timestamp, Op);
							});
						}
					}
					else if (ReceivedStreamType.StartsWith(TEXT("error")))
					{
						FBeamCliError Data = FBeamCliError{};
						Data.OuterOwner = this;
						Data.BeamDeserializeProperties(DataJson);

						Errors.Add(Data);
						ErrorsTimestamps.Add(Timestamp);

						if (OnErrorsStreamOutput)
						{
							AsyncTask(ENamedThreads::GameThread, [this, Op]
							{
								OnErrorsStreamOutput(Errors, ErrorsTimestamps, Op);
							});
						}
						else
						{
							UE_LOG(LogBeamCli, Error, TEXT("BeamCli Command - Error. CMD=%s, MESSAGE=%s"), *Params, *MessageJson);
						}
					}
					else
					{
						UE_LOG(LogBeamCli, Warning, TEXT("BeamCli Command - Skipping unknown message format. CMD=%s, MESSAGE=%s"), *Params, *MessageJson);
					}
				}
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
		this->Cli->OnCommandCompleted(this);
	});
}

bool UBeamCliCommand::IsDone() const
{
	if (CmdProcess.IsValid())
		return CmdProcess->Update();

	if (CmdRequest.IsValid())
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

bool UBeamCliCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	return false;
}

void UBeamCliCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
}
