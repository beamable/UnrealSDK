#include "BeamCliServicesGetConnectionStringCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesGetConnectionStringCommand::GetCommand()
{
	return FString(TEXT("services get-connection-string"));
}
		
bool UBeamCliServicesGetConnectionStringCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesGetConnectionStringStreamData* Data = NewObject<UBeamCliServicesGetConnectionStringStreamData>(this);
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

void UBeamCliServicesGetConnectionStringCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}