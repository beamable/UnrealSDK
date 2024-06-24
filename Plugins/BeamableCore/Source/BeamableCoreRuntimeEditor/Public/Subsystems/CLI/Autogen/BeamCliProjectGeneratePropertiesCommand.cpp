#include "BeamCliProjectGeneratePropertiesCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliProjectGeneratePropertiesCommand::GetCommand()
{
	return FString(TEXT("project generate-properties"));
}
		
void UBeamCliProjectGeneratePropertiesCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
}

void UBeamCliProjectGeneratePropertiesCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
