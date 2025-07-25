
#include "BeamableCore/Public/AutoGen/GetPricesRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetPricesRequestBodyLibrary::GetPricesRequestBodyToJsonString(const UGetPricesRequestBody* Serializable, const bool Pretty)
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

UGetPricesRequestBody* UGetPricesRequestBodyLibrary::Make(int64 SteamId, UObject* Outer)
{
	auto Serializable = NewObject<UGetPricesRequestBody>(Outer);
	Serializable->SteamId = SteamId;
	
	return Serializable;
}

void UGetPricesRequestBodyLibrary::Break(const UGetPricesRequestBody* Serializable, int64& SteamId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SteamId = Serializable->SteamId;
	}
		
}

