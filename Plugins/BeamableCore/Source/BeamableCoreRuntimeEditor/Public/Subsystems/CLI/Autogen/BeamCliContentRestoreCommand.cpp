#include "BeamCliContentRestoreCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliContentRestoreCommand::GetCommand()
{
	return FString(TEXT("content restore"));
}
		
bool UBeamCliContentRestoreCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliContentRestoreStreamData* Data = NewObject<UBeamCliContentRestoreStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			Stream.Add(Data);
			Timestamps.Add(Timestamp);
		
		
			OnStreamOutput(Stream, Timestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeErrorContentRestoreErrorReport) && OnErrorContentRestoreErrorReportStreamOutput)
	{
		AsyncTask(ENamedThreads::GameThread, [this, DataJson, Timestamp, Op]
		{
			UBeamCliContentRestoreErrorContentRestoreErrorReportStreamData* Data = NewObject<UBeamCliContentRestoreErrorContentRestoreErrorReportStreamData>(this);
			Data->OuterOwner = this;
			Data->BeamDeserializeProperties(DataJson);

			ErrorContentRestoreErrorReportStream.Add(Data);
			ErrorContentRestoreErrorReportTimestamps.Add(Timestamp);
		
		
			OnErrorContentRestoreErrorReportStreamOutput(ErrorContentRestoreErrorReportStream, ErrorContentRestoreErrorReportTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliContentRestoreCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
