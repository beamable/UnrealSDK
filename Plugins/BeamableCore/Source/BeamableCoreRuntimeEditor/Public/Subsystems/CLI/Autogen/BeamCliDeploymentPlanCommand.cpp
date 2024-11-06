#include "BeamCliDeploymentPlanCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliDeploymentPlanCommand::GetCommand()
{
	return FString(TEXT("deployment plan"));
}
		
bool UBeamCliDeploymentPlanCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliDeploymentPlanStreamData* Data = NewObject<UBeamCliDeploymentPlanStreamData>(this);
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

	if(ReceivedStreamType.Equals(StreamTypeBuildErrors) && OnBuildErrorsStreamOutput)
	{
		UBeamCliDeploymentPlanBuildErrorsStreamData* Data = NewObject<UBeamCliDeploymentPlanBuildErrorsStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		BuildErrorsStream.Add(Data);
		BuildErrorsTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnBuildErrorsStreamOutput(BuildErrorsStream, BuildErrorsTimestamps, Op);
		});
		
		return true;				
	}

	if(ReceivedStreamType.Equals(StreamTypeProgress) && OnProgressStreamOutput)
	{
		UBeamCliDeploymentPlanProgressStreamData* Data = NewObject<UBeamCliDeploymentPlanProgressStreamData>(this);
		Data->OuterOwner = this;
		Data->BeamDeserializeProperties(DataJson);

		ProgressStream.Add(Data);
		ProgressTimestamps.Add(Timestamp);
		
		AsyncTask(ENamedThreads::GameThread, [this, Op]
		{
			OnProgressStreamOutput(ProgressStream, ProgressTimestamps, Op);
		});
		
		return true;				
	}
	
	return false;
}

void UBeamCliDeploymentPlanCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
