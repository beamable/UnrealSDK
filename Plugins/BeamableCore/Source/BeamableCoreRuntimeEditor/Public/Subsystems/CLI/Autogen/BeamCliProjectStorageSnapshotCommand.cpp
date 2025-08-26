#include "BeamCliProjectStorageSnapshotCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliProjectStorageSnapshotCommand::GetCommand()
{
	return FString(TEXT("project storage snapshot"));
}
		
bool UBeamCliProjectStorageSnapshotCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliProjectStorageSnapshotStreamData* Data = NewObject<UBeamCliProjectStorageSnapshotStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeMongoLogs) && OnMongoLogsStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliProjectStorageSnapshotMongoLogsStreamData* Data = NewObject<UBeamCliProjectStorageSnapshotMongoLogsStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			MongoLogsStream.Add(Data);
			MongoLogsTimestamps.Add(Timestamp);
		
		
			OnMongoLogsStreamOutput(MongoLogsStream, MongoLogsTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliProjectStorageSnapshotCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
