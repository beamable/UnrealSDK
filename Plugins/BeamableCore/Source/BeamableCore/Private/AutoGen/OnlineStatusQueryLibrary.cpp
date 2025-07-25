
#include "BeamableCore/Public/AutoGen/OnlineStatusQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOnlineStatusQueryLibrary::OnlineStatusQueryToJsonString(const UOnlineStatusQuery* Serializable, const bool Pretty)
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

UOnlineStatusQuery* UOnlineStatusQueryLibrary::Make(FOptionalArrayOfString PlayerIds, UObject* Outer)
{
	auto Serializable = NewObject<UOnlineStatusQuery>(Outer);
	Serializable->PlayerIds = PlayerIds;
	
	return Serializable;
}

void UOnlineStatusQueryLibrary::Break(const UOnlineStatusQuery* Serializable, FOptionalArrayOfString& PlayerIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerIds = Serializable->PlayerIds;
	}
		
}

