#include "BeamCliContentPsCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliContentPsCommand::GetCommand()
{
	return FString(TEXT("content ps"));
}
		
bool UBeamCliContentPsCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliContentPsStreamData* Data = NewObject<UBeamCliContentPsStreamData>(this);
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
			UBeamCliContentPsProgressStreamStreamData* Data = NewObject<UBeamCliContentPsProgressStreamStreamData>(this);
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

void UBeamCliContentPsCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
