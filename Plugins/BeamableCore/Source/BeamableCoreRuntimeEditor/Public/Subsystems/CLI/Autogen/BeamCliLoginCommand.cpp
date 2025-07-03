#include "BeamCliLoginCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliLoginCommand::GetCommand()
{
	return FString(TEXT("login"));
}
		
bool UBeamCliLoginCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamTypeErrorLoginFailedError) && OnErrorLoginFailedErrorStreamOutput)
	{
		UBeamCliLoginErrorLoginFailedErrorStreamData* Data = NewObject<UBeamCliLoginErrorLoginFailedErrorStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliLoginStreamData* Data = NewObject<UBeamCliLoginStreamData>(this);
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
	
	return false;
}

void UBeamCliLoginCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
