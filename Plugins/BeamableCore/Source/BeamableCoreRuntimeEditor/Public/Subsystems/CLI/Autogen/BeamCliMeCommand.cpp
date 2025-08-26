#include "BeamCliMeCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliMeCommand::GetCommand()
{
	return FString(TEXT("me"));
}
		
bool UBeamCliMeCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliMeStreamData* Data = NewObject<UBeamCliMeStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorNoTokenError) && OnErrorNoTokenErrorStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliMeErrorNoTokenErrorStreamData* Data = NewObject<UBeamCliMeErrorNoTokenErrorStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ErrorNoTokenErrorStream.Add(Data);
			ErrorNoTokenErrorTimestamps.Add(Timestamp);
		
		
			OnErrorNoTokenErrorStreamOutput(ErrorNoTokenErrorStream, ErrorNoTokenErrorTimestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorInvalidTokenError) && OnErrorInvalidTokenErrorStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliMeErrorInvalidTokenErrorStreamData* Data = NewObject<UBeamCliMeErrorInvalidTokenErrorStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ErrorInvalidTokenErrorStream.Add(Data);
			ErrorInvalidTokenErrorTimestamps.Add(Timestamp);
		
		
			OnErrorInvalidTokenErrorStreamOutput(ErrorInvalidTokenErrorStream, ErrorInvalidTokenErrorTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliMeCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
