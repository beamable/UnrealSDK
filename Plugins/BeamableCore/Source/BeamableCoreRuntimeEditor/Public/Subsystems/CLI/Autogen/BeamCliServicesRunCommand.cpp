#include "BeamCliServicesRunCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesRunCommand::GetCommand()
{
	return FString(TEXT("services run"));
}
		
bool UBeamCliServicesRunCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesRunStreamData* Data = NewObject<UBeamCliServicesRunStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeLocalProgress) && OnLocalProgressStreamOutput)
	{
		UBeamCliServicesRunLocalProgressStreamData* Data = NewObject<UBeamCliServicesRunLocalProgressStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		LocalProgressStream.Add(Data);
		LocalProgressTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnLocalProgressStreamOutput(LocalProgressStream, LocalProgressTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliServicesRunCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
