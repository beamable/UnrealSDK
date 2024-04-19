#include "BeamCliServicesRunCommand.h"

#include "BeamLogging.h"
#include "Misc/MonitoredProcess.h"
#include "Serialization/JsonSerializerMacros.h"
		
TSharedPtr<FMonitoredProcess> UBeamCliServicesRunCommand::RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	FString Params = ("services run");
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Invocation: %s %s"), *PathToCli, *Params)

	const auto CliPath = Cli->GetPathToCli();
	const auto CliProcess = MakeShared<FMonitoredProcess>(CliPath, Params, FPaths::ProjectDir(), true, true);
	CliProcess->OnOutput().BindLambda([this, Op](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Std Out: %s"), *Out);
		FString OutCopy = Out;
		FString MessageJson;
		while (ConsumeMessageFromOutput(OutCopy, MessageJson))
		{
			auto Bag = FJsonDataBag();
			if (Bag.FromJson(MessageJson))
			{
				const auto ReceivedStreamType = Bag.GetString("type");
				const auto Timestamp = static_cast<int64>(Bag.GetField("ts")->AsNumber());
				const auto DataJson = Bag.JsonObject->GetObjectField("data").ToSharedRef();
				
				
				if(ReceivedStreamType.Equals(StreamType))
				{
					UBeamCliServicesRunStreamData* Data = NewObject<UBeamCliServicesRunStreamData>(this);
					Data->OuterOwner = this;
					Data->BeamDeserializeProperties(DataJson);

					Stream.Add(Data);
					Timestamps.Add(Timestamp);

					UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Message Received: %s"), *MessageJson);
					AsyncTask(ENamedThreads::GameThread, [this, Op]
					{
						OnStreamOutput(Stream, Timestamps, Op);
					});				
				}


				if(ReceivedStreamType.Equals(StreamTypeLocalProgress))
				{
					UBeamCliServicesRunLocalProgressStreamData* Data = NewObject<UBeamCliServicesRunLocalProgressStreamData>(this);
					Data->OuterOwner = this;
					Data->BeamDeserializeProperties(DataJson);

					LocalProgressStream.Add(Data);
					LocalProgressTimestamps.Add(Timestamp);

					UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Message Received: %s"), *MessageJson);
					AsyncTask(ENamedThreads::GameThread, [this, Op]
					{
						OnLocalProgressStreamOutput(LocalProgressStream, LocalProgressTimestamps, Op);
					});				
				}

			}
			else
			{
				UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Skipping non-JSON message: %s"), *MessageJson);
			}			
		}
	});
	CliProcess->OnCompleted().BindLambda([this, Op](int ResultCode)
	{
		if (OnCompleted)
		{
			AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
			{
				OnCompleted(ResultCode, Op);
			});
		}
	});
	return CliProcess;
}
