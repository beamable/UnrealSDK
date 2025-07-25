
#include "BeamableCore/Public/AutoGen/PlayerBasicCloudDataRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerBasicCloudDataRequestBodyLibrary::PlayerBasicCloudDataRequestBodyToJsonString(const UPlayerBasicCloudDataRequestBody* Serializable, const bool Pretty)
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

UPlayerBasicCloudDataRequestBody* UPlayerBasicCloudDataRequestBodyLibrary::Make(FOptionalInt64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerBasicCloudDataRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UPlayerBasicCloudDataRequestBodyLibrary::Break(const UPlayerBasicCloudDataRequestBody* Serializable, FOptionalInt64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

