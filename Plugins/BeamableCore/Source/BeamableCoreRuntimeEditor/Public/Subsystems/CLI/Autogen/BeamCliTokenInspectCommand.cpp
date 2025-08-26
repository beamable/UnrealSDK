#include "BeamCliTokenInspectCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliTokenInspectCommand::GetCommand()
{
	return FString(TEXT("token inspect"));
}
		
bool UBeamCliTokenInspectCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliTokenInspectStreamData* Data = NewObject<UBeamCliTokenInspectStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorInvalidTokenErrorOutput) && OnErrorInvalidTokenErrorOutputStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData* Data = NewObject<UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ErrorInvalidTokenErrorOutputStream.Add(Data);
			ErrorInvalidTokenErrorOutputTimestamps.Add(Timestamp);
		
		
			OnErrorInvalidTokenErrorOutputStreamOutput(ErrorInvalidTokenErrorOutputStream, ErrorInvalidTokenErrorOutputTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliTokenInspectCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
