#include "BeamCliServicesRunCommand.h"

#include "BeamLogging.h"
#include "Misc/MonitoredProcess.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializerMacros.h"
		
TSharedPtr<FMonitoredProcess> UBeamCliServicesRunCommand::RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	FString Params = ("services run --reporter-use-fatal");
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Invocation: %s %s"), *PathToCli, *Params)

	const auto CliProcess = MakeShared<FMonitoredProcess>(PathToCli, Params, FPaths::ProjectDir(), true, true);
	CliProcess->OnOutput().BindLambda([this, Op](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesRun Command - Std Out: %s"), *Out);
		FString OutCopy = Out;
		FString MessageJson;
		while (ConsumeMessageFromOutput(OutCopy, MessageJson))
		{
			auto Bag = FJsonDataBag();
			Bag.FromJson(MessageJson);
			const auto ReceivedStreamType = Bag.GetString("type");
			const auto Timestamp = static_cast<int64>(Bag.GetField("ts")->AsNumber());
			const auto DataJson = Bag.JsonObject->GetObjectField("data").ToSharedRef();

			
			if(ReceivedStreamType.Equals(StreamType))
			{
				UBeamCliServicesRunStreamData* Data = NewObject<UBeamCliServicesRunStreamData>();
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
				UBeamCliServicesRunLocalProgressStreamData* Data = NewObject<UBeamCliServicesRunLocalProgressStreamData>();
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
