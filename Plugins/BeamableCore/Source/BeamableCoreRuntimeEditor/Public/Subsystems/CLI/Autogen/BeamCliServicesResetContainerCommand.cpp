#include "BeamCliServicesResetContainerCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesResetContainerCommand::GetCommand()
{
	return FString(TEXT("services reset container"));
}
		
void UBeamCliServicesResetContainerCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesResetContainerStreamData* Data = NewObject<UBeamCliServicesResetContainerStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		Stream.Add(Data);
		Timestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnStreamOutput(Stream, Timestamps, Op);
		});				
	}
}

void UBeamCliServicesResetContainerCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
