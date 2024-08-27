#include "BeamCliTokenInspectCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliTokenInspectCommand::GetCommand()
{
	return FString(TEXT("token inspect"));
}
		
void UBeamCliTokenInspectCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliTokenInspectStreamData* Data = NewObject<UBeamCliTokenInspectStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		Stream.Add(Data);
		Timestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnStreamOutput(Stream, Timestamps, Op);
		});				
	}
if(ReceivedStreamType.Equals(StreamTypeErrorInvalidTokenErrorOutput) && OnErrorInvalidTokenErrorOutputStreamOutput)
	{
		UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData* Data = NewObject<UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ErrorInvalidTokenErrorOutputStream.Add(Data);
		ErrorInvalidTokenErrorOutputTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnErrorInvalidTokenErrorOutputStreamOutput(ErrorInvalidTokenErrorOutputStream, ErrorInvalidTokenErrorOutputTimestamps, Op);
		});				
	}
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
