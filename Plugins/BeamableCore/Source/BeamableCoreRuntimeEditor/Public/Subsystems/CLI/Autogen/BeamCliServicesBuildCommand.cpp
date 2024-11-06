#include "BeamCliServicesBuildCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesBuildCommand::GetCommand()
{
	return FString(TEXT("services build"));
}
		
bool UBeamCliServicesBuildCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesBuildStreamData* Data = NewObject<UBeamCliServicesBuildStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeProgress) && OnProgressStreamOutput)
	{
		UBeamCliServicesBuildProgressStreamData* Data = NewObject<UBeamCliServicesBuildProgressStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ProgressStream.Add(Data);
		ProgressTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnProgressStreamOutput(ProgressStream, ProgressTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliServicesBuildCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
