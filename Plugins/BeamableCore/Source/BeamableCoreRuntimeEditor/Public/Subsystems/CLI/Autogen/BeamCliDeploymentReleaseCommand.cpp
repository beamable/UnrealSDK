#include "BeamCliDeploymentReleaseCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliDeploymentReleaseCommand::GetCommand()
{
	return FString(TEXT("deployment release"));
}
		
bool UBeamCliDeploymentReleaseCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliDeploymentReleaseStreamData* Data = NewObject<UBeamCliDeploymentReleaseStreamData>(this);
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
		UBeamCliDeploymentReleaseBuildErrorsStreamData* Data = NewObject<UBeamCliDeploymentReleaseBuildErrorsStreamData>(this);
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
		UBeamCliDeploymentReleaseProgressStreamData* Data = NewObject<UBeamCliDeploymentReleaseProgressStreamData>(this);
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

void UBeamCliDeploymentReleaseCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
