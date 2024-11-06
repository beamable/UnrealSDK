#include "BeamCliProjectStorageRestoreCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliProjectStorageRestoreCommand::GetCommand()
{
	return FString(TEXT("project storage restore"));
}
		
bool UBeamCliProjectStorageRestoreCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliProjectStorageRestoreStreamData* Data = NewObject<UBeamCliProjectStorageRestoreStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeMongoLogs) && OnMongoLogsStreamOutput)
	{
		UBeamCliProjectStorageRestoreMongoLogsStreamData* Data = NewObject<UBeamCliProjectStorageRestoreMongoLogsStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		MongoLogsStream.Add(Data);
		MongoLogsTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnMongoLogsStreamOutput(MongoLogsStream, MongoLogsTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliProjectStorageRestoreCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
