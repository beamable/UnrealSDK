
#include "BeamableCore/Public/AutoGen/PlayerIdRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerIdRequestBodyLibrary::PlayerIdRequestBodyToJsonString(const UPlayerIdRequestBody* Serializable, const bool Pretty)
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

UPlayerIdRequestBody* UPlayerIdRequestBodyLibrary::Make(FBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerIdRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UPlayerIdRequestBodyLibrary::Break(const UPlayerIdRequestBody* Serializable, FBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

