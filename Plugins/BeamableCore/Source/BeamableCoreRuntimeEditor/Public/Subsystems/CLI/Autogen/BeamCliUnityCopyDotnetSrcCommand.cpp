#include "BeamCliUnityCopyDotnetSrcCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliUnityCopyDotnetSrcCommand::GetCommand()
{
	return FString(TEXT("unity copy-dotnet-src"));
}
		
void UBeamCliUnityCopyDotnetSrcCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliUnityCopyDotnetSrcStreamData* Data = NewObject<UBeamCliUnityCopyDotnetSrcStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		Stream.Add(Data);
		Timestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnStreamOutput(Stream, Timestamps, Op);
		});				
	}
}

void UBeamCliUnityCopyDotnetSrcCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
