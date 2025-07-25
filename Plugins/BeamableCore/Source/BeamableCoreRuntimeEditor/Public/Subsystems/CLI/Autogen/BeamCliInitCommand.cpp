#include "BeamCliInitCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliInitCommand::GetCommand()
{
	return FString(TEXT("init"));
}
		
bool UBeamCliInitCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliInitStreamData* Data = NewObject<UBeamCliInitStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeErrorLoginFailedError) && OnErrorLoginFailedErrorStreamOutput)
	{
		UBeamCliInitErrorLoginFailedErrorStreamData* Data = NewObject<UBeamCliInitErrorLoginFailedErrorStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ErrorLoginFailedErrorStream.Add(Data);
		ErrorLoginFailedErrorTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnErrorLoginFailedErrorStreamOutput(ErrorLoginFailedErrorStream, ErrorLoginFailedErrorTimestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorInvalidCidError) && OnErrorInvalidCidErrorStreamOutput)
	{
		UBeamCliInitErrorInvalidCidErrorStreamData* Data = NewObject<UBeamCliInitErrorInvalidCidErrorStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ErrorInvalidCidErrorStream.Add(Data);
		ErrorInvalidCidErrorTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnErrorInvalidCidErrorStreamOutput(ErrorInvalidCidErrorStream, ErrorInvalidCidErrorTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliInitCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
