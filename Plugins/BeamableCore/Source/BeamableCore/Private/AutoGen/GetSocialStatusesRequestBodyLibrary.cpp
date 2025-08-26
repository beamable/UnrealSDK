
#include "BeamableCore/Public/AutoGen/GetSocialStatusesRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSocialStatusesRequestBodyLibrary::GetSocialStatusesRequestBodyToJsonString(const UGetSocialStatusesRequestBody* Serializable, const bool Pretty)
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

UGetSocialStatusesRequestBody* UGetSocialStatusesRequestBodyLibrary::Make(TArray<FString> PlayerIds, UObject* Outer)
{
	auto Serializable = NewObject<UGetSocialStatusesRequestBody>(Outer);
	Serializable->PlayerIds = PlayerIds;
	
	return Serializable;
}

void UGetSocialStatusesRequestBodyLibrary::Break(const UGetSocialStatusesRequestBody* Serializable, TArray<FString>& PlayerIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerIds = Serializable->PlayerIds;
	}
		
}

