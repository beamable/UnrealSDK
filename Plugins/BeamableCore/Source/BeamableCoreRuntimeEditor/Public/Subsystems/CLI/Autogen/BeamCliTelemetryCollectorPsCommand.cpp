#include "BeamCliTelemetryCollectorPsCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliTelemetryCollectorPsCommand::GetCommand()
{
	return FString(TEXT("telemetry collector ps"));
}
		
bool UBeamCliTelemetryCollectorPsCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliTelemetryCollectorPsStreamData* Data = NewObject<UBeamCliTelemetryCollectorPsStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeExtraStream) && OnExtraStreamStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliTelemetryCollectorPsExtraStreamStreamData* Data = NewObject<UBeamCliTelemetryCollectorPsExtraStreamStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ExtraStreamStream.Add(Data);
			ExtraStreamTimestamps.Add(Timestamp);
		
		
			OnExtraStreamStreamOutput(ExtraStreamStream, ExtraStreamTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliTelemetryCollectorPsCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
