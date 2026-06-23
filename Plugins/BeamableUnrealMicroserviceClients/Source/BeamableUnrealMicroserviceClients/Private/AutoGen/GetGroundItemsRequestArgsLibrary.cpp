
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroundItemsRequestArgsLibrary::GetGroundItemsRequestArgsToJsonString(const UGetGroundItemsRequestArgs* Serializable, const bool Pretty)
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

UGetGroundItemsRequestArgs* UGetGroundItemsRequestArgsLibrary::Make(FString SpawnerId, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroundItemsRequestArgs>(Outer);
	Serializable->SpawnerId = SpawnerId;
	
	return Serializable;
}

void UGetGroundItemsRequestArgsLibrary::Break(const UGetGroundItemsRequestArgs* Serializable, FString& SpawnerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SpawnerId = Serializable->SpawnerId;
	}
		
}

