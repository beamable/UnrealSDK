#include "BeamCliServicesPsCommand.h"

#include "BeamLogging.h"
#include "Misc/MonitoredProcess.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializerMacros.h"
		
TSharedPtr<FMonitoredProcess> UBeamCliServicesPsCommand::RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	FString Params = ("services ps --reporter-use-fatal");
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesPs Command - Invocation: %s %s"), *PathToCli, *Params)

	const auto CliProcess = MakeShared<FMonitoredProcess>(PathToCli, Params, FPaths::ProjectDir(), true, true);
	CliProcess->OnOutput().BindLambda([this, Op](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesPs Command - Std Out: %s"), *Out);
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
				UBeamCliServicesPsStreamData* Data = NewObject<UBeamCliServicesPsStreamData>();
				Data->BeamDeserializeProperties(DataJson);

				Stream.Add(Data);
				Timestamps.Add(Timestamp);

				UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesPs Command - Message Received: %s"), *MessageJson);
				AsyncTask(ENamedThreads::GameThread, [this, Op]
				{
					OnStreamOutput(Stream, Timestamps, Op);
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
