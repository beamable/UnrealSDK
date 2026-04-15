#include "BeamCliPortalExtensionAddMicroserviceCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliPortalExtensionAddMicroserviceCommand::GetCommand()
{
	return FString(TEXT("portal extension add-microservice"));
}
		
bool UBeamCliPortalExtensionAddMicroserviceCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	
	return false;
}

void UBeamCliPortalExtensionAddMicroserviceCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
