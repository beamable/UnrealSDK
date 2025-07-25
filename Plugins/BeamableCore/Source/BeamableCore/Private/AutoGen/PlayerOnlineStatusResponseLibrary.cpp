
#include "BeamableCore/Public/AutoGen/PlayerOnlineStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerOnlineStatusResponseLibrary::PlayerOnlineStatusResponseToJsonString(const UPlayerOnlineStatusResponse* Serializable, const bool Pretty)
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

UPlayerOnlineStatusResponse* UPlayerOnlineStatusResponseLibrary::Make(bool bOnline, int64 PlayerId, int64 LastSeen, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerOnlineStatusResponse>(Outer);
	Serializable->bOnline = bOnline;
	Serializable->PlayerId = PlayerId;
	Serializable->LastSeen = LastSeen;
	
	return Serializable;
}

void UPlayerOnlineStatusResponseLibrary::Break(const UPlayerOnlineStatusResponse* Serializable, bool& bOnline, int64& PlayerId, int64& LastSeen)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bOnline = Serializable->bOnline;
		PlayerId = Serializable->PlayerId;
		LastSeen = Serializable->LastSeen;
	}
		
}

