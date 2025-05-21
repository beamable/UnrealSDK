#include "BeamCliChecksScanCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliChecksScanCommand::GetCommand()
{
	return FString(TEXT("checks scan"));
}
		
bool UBeamCliChecksScanCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliChecksScanStreamData* Data = NewObject<UBeamCliChecksScanStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeFixedKey) && OnFixedKeyStreamOutput)
	{
		UBeamCliChecksScanFixedKeyStreamData* Data = NewObject<UBeamCliChecksScanFixedKeyStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		FixedKeyStream.Add(Data);
		FixedKeyTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnFixedKeyStreamOutput(FixedKeyStream, FixedKeyTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliChecksScanCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
