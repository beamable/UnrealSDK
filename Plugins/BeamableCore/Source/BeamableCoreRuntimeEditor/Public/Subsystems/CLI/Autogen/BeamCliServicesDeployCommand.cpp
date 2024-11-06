#include "BeamCliServicesDeployCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesDeployCommand::GetCommand()
{
	return FString(TEXT("services deploy"));
}
		
bool UBeamCliServicesDeployCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesDeployStreamData* Data = NewObject<UBeamCliServicesDeployStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeRemoteProgress) && OnRemoteProgressStreamOutput)
	{
		UBeamCliServicesDeployRemoteProgressStreamData* Data = NewObject<UBeamCliServicesDeployRemoteProgressStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		RemoteProgressStream.Add(Data);
		RemoteProgressTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnRemoteProgressStreamOutput(RemoteProgressStream, RemoteProgressTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliServicesDeployCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
