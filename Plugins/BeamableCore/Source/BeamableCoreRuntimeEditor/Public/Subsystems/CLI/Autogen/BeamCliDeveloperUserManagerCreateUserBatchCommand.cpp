#include "BeamCliDeveloperUserManagerCreateUserBatchCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliDeveloperUserManagerCreateUserBatchCommand::GetCommand()
{
	return FString(TEXT("developer-user-manager create-user-batch"));
}
		
bool UBeamCliDeveloperUserManagerCreateUserBatchCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliDeveloperUserManagerCreateUserBatchStreamData* Data = NewObject<UBeamCliDeveloperUserManagerCreateUserBatchStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliDeveloperUserManagerCreateUserBatchCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
