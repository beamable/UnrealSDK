
#include "BeamableCore/Public/AutoGen/ApiSessionsHeartbeatPostSessionResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiSessionsHeartbeatPostSessionResponseLibrary::ApiSessionsHeartbeatPostSessionResponseToJsonString(const UApiSessionsHeartbeatPostSessionResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UApiSessionsHeartbeatPostSessionResponse* UApiSessionsHeartbeatPostSessionResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiSessionsHeartbeatPostSessionResponse>(Outer);
	
	return Serializable;
}



