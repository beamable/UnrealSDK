#include "BeamCliOtelCollectorCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliOtelCollectorCommand::GetCommand()
{
	return FString(TEXT("otel collector"));
}
		
bool UBeamCliOtelCollectorCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	
	return false;
}

void UBeamCliOtelCollectorCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
