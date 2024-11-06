#include "BeamCliUnityDownloadAllNugetPackagesCommand.h"

#include "BeamLogging.h"
#include "Serialization/JsonSerializerMacros.h"

FString UBeamCliUnityDownloadAllNugetPackagesCommand::GetCommand()
{
	return FString(TEXT("unity download-all-nuget-packages"));
}
		
bool UBeamCliUnityDownloadAllNugetPackagesCommand::HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer)
{
	
	if(ReceivedStreamType.Equals(StreamType) && OnStreamOutput)
	{
		UBeamCliUnityDownloadAllNugetPackagesStreamData* Data = NewObject<UBeamCliUnityDownloadAllNugetPackagesStreamData>(this);
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
	
	return false;
}

void UBeamCliUnityDownloadAllNugetPackagesCommand::HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer)
{
	if (OnCompleted)
	{
		AsyncTask(ENamedThreads::GameThread, [this, ResultCode, Op]
		{
			OnCompleted(ResultCode, Op);
		});
	}
}
