#include "BeamCliCollectorGetCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliCollectorGetCommand::GetCommand()
{
	return FString(TEXT("collector get"));
}
		
bool UBeamCliCollectorGetCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliCollectorGetStreamData* Data = NewObject<UBeamCliCollectorGetStreamData>(this);
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

void UBeamCliCollectorGetCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
