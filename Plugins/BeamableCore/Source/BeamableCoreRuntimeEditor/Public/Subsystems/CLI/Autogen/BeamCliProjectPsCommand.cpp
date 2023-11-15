#include "BeamCliProjectPsCommand.h"

#include "BeamLogging.h"
#include "Misc/MonitoredProcess.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializerMacros.h"
		
TSharedPtr<FMonitoredProcess> UBeamCliProjectPsCommand::RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	FString Params = ("project ps --reporter-use-fatal");
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliProjectPs Command - Invocation: %s %s"), *PathToCli, *Params)

	const auto CliProcess = MakeShared<FMonitoredProcess>(PathToCli, Params, FPaths::ProjectDir(), true, true);
	CliProcess->OnOutput().BindLambda([this, Op](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliProjectPs Command - Std Out: %s"), *Out);
		FString OutCopy = Out;
		FString MessageJson;
		while (ConsumeMessageFromOutput(OutCopy, MessageJson))
		{
			auto Bag = FJsonDataBag();
			Bag.FromJson(MessageJson);
			const auto StreamType = Bag.GetString("type");
			const auto Timestamp = static_cast<int64>(Bag.GetField("ts")->AsNumber());
			const auto DataJson = Bag.JsonObject->GetObjectField("data").ToSharedRef();

			
			if(StreamType.Equals(FBeamCliProjectPsStreamData::StreamTypeName))
			{
				FBeamCliProjectPsStreamData Data;
				FJsonObjectConverter::JsonObjectToUStruct(DataJson, FBeamCliProjectPsStreamData::StaticStruct(), &Data);

				Stream.Add(Data);
				Timestamps.Add(Timestamp);

				UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliProjectPs Command - Message Received: %s"), *MessageJson);
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
