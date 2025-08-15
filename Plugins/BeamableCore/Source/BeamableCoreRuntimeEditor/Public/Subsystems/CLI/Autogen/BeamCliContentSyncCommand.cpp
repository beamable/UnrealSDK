#include "BeamCliContentSyncCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliContentSyncCommand::GetCommand()
{
	return FString(TEXT("content sync"));
}
		
bool UBeamCliContentSyncCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliContentSyncStreamData* Data = NewObject<UBeamCliContentSyncStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeProgressStream) && OnProgressStreamStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliContentSyncProgressStreamStreamData* Data = NewObject<UBeamCliContentSyncProgressStreamStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ProgressStreamStream.Add(Data);
			ProgressStreamTimestamps.Add(Timestamp);
		
		
			OnProgressStreamStreamOutput(ProgressStreamStream, ProgressStreamTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliContentSyncCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
