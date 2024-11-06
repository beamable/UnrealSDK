#include "BeamCliFederationLocalSettingsSetIFederatedGameServerCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliFederationLocalSettingsSetIFederatedGameServerCommand::GetCommand()
{
	return FString(TEXT("federation local-settings set IFederatedGameServer"));
}
		
bool UBeamCliFederationLocalSettingsSetIFederatedGameServerCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliFederationLocalSettingsSetIFederatedGameServerStreamData* Data = NewObject<UBeamCliFederationLocalSettingsSetIFederatedGameServerStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		Stream.Add(Data);
		Timestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliFederationLocalSettingsSetIFederatedGameServerCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
