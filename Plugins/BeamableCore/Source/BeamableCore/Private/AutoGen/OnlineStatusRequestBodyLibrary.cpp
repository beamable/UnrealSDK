
#include "BeamableCore/Public/AutoGen/OnlineStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOnlineStatusRequestBodyLibrary::OnlineStatusRequestBodyToJsonString(const UOnlineStatusRequestBody* Serializable, const bool Pretty)
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

UOnlineStatusRequestBody* UOnlineStatusRequestBodyLibrary::Make(FString PlayerIds, int64 IntervalSecs, UObject* Outer)
{
	auto Serializable = NewObject<UOnlineStatusRequestBody>(Outer);
	Serializable->PlayerIds = PlayerIds;
	Serializable->IntervalSecs = IntervalSecs;
	
	return Serializable;
}

void UOnlineStatusRequestBodyLibrary::Break(const UOnlineStatusRequestBody* Serializable, FString& PlayerIds, int64& IntervalSecs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerIds = Serializable->PlayerIds;
		IntervalSecs = Serializable->IntervalSecs;
	}
		
}

