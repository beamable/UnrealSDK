#include "BeamCliServicesStopCommand.h"

#include "BeamLogging.h"
#include "Misc/MonitoredProcess.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializerMacros.h"
		
TSharedPtr<FMonitoredProcess> UBeamCliServicesStopCommand::RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op)
{
	FString Params = ("services stop --reporter-use-fatal");
	for (const auto& CommandParam : CommandParams)
		Params.Appendf(TEXT(" %s"), *CommandParam);
	Params = PrepareParams(Params);
	UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesStop Command - Invocation: %s %s"), *PathToCli, *Params)

	const auto CliProcess = MakeShared<FMonitoredProcess>(PathToCli, Params, FPaths::ProjectDir(), true, true);
	CliProcess->OnOutput().BindLambda([this, Op](const FString& Out)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("BeamCliServicesStop Command - Std Out: %s"), *Out);
		FString OutCopy = Out;
		FString MessageJson;
		while (ConsumeMessageFromOutput(OutCopy, MessageJson))
		{
			auto Bag = FJsonDataBag();
			Bag.FromJson(MessageJson);
			const auto StreamType = Bag.GetString("type");
			const auto Timestamp = static_cast<int64>(Bag.GetField("ts")->AsNumber());
			const auto DataJson = Bag.JsonObject->GetObjectField("data").ToSharedRef();

			
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
