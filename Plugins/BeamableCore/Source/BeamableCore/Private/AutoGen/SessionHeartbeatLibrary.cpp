
#include "BeamableCore/Public/AutoGen/SessionHeartbeatLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionHeartbeatLibrary::SessionHeartbeatToJsonString(const USessionHeartbeat* Serializable, const bool Pretty)
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

USessionHeartbeat* USessionHeartbeatLibrary::Make(int64 Gt, FOptionalInt64 Heartbeat, UObject* Outer)
{
	auto Serializable = NewObject<USessionHeartbeat>(Outer);
	Serializable->Gt = Gt;
	Serializable->Heartbeat = Heartbeat;
	
	return Serializable;
}

void USessionHeartbeatLibrary::Break(const USessionHeartbeat* Serializable, int64& Gt, FOptionalInt64& Heartbeat)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Gt = Serializable->Gt;
		Heartbeat = Serializable->Heartbeat;
	}
		
}

