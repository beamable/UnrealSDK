#include "BeamCliProjectStorageEraseCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliProjectStorageEraseCommand::GetCommand()
{
	return FString(TEXT("project storage erase"));
}
		
bool UBeamCliProjectStorageEraseCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliProjectStorageEraseStreamData* Data = NewObject<UBeamCliProjectStorageEraseStreamData>(this);
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
		UBeamCliProjectStorageEraseMongoLogsStreamData* Data = NewObject<UBeamCliProjectStorageEraseMongoLogsStreamData>(this);
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

void UBeamCliProjectStorageEraseCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
