#include "BeamCliProjectRunCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliProjectRunCommand::GetCommand()
{
	return FString(TEXT("project run"));
}
		
bool UBeamCliProjectRunCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliProjectRunStreamData* Data = NewObject<UBeamCliProjectRunStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeBuildErrors) && OnBuildErrorsStreamOutput)
	{
		UBeamCliProjectRunBuildErrorsStreamData* Data = NewObject<UBeamCliProjectRunBuildErrorsStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		BuildErrorsStream.Add(Data);
		BuildErrorsTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnBuildErrorsStreamOutput(BuildErrorsStream, BuildErrorsTimestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorRunFailErrorOutput) && OnErrorRunFailErrorOutputStreamOutput)
	{
		UBeamCliProjectRunErrorRunFailErrorOutputStreamData* Data = NewObject<UBeamCliProjectRunErrorRunFailErrorOutputStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ErrorRunFailErrorOutputStream.Add(Data);
		ErrorRunFailErrorOutputTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnErrorRunFailErrorOutputStreamOutput(ErrorRunFailErrorOutputStream, ErrorRunFailErrorOutputTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliProjectRunCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
