
#include "BeamableCore/Public/AutoGen/OnlineStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOnlineStatusLibrary::OnlineStatusToJsonString(const UOnlineStatus* Serializable, const bool Pretty)
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

UOnlineStatus* UOnlineStatusLibrary::Make(FOptionalDateTime LastOnline, FOptionalBool bOnline, FOptionalBeamGamerTag PlayerId, FOptionalPresenceStatus Status, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<UOnlineStatus>(Outer);
	Serializable->LastOnline = LastOnline;
	Serializable->bOnline = bOnline;
	Serializable->PlayerId = PlayerId;
	Serializable->Status = Status;
	Serializable->Description = Description;
	
	return Serializable;
}

void UOnlineStatusLibrary::Break(const UOnlineStatus* Serializable, FOptionalDateTime& LastOnline, FOptionalBool& bOnline, FOptionalBeamGamerTag& PlayerId, FOptionalPresenceStatus& Status, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LastOnline = Serializable->LastOnline;
		bOnline = Serializable->bOnline;
		PlayerId = Serializable->PlayerId;
		Status = Serializable->Status;
		Description = Serializable->Description;
	}
		
}

