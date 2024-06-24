#include "BeamCliServicesServiceMetricsCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliServicesServiceMetricsCommand::GetCommand()
{
	return FString(TEXT("services service-metrics"));
}
		
void UBeamCliServicesServiceMetricsCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliServicesServiceMetricsStreamData* Data = NewObject<UBeamCliServicesServiceMetricsStreamData>(this);
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

void UBeamCliServicesServiceMetricsCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
