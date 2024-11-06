#include "BeamCliUnityUpdateReferencesCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliUnityUpdateReferencesCommand::GetCommand()
{
	return FString(TEXT("unity update-references"));
}
		
bool UBeamCliUnityUpdateReferencesCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	
	return false;
}

void UBeamCliUnityUpdateReferencesCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
