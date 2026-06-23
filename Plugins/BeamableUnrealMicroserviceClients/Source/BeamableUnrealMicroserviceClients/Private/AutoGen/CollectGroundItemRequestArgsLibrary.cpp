
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectGroundItemRequestArgsLibrary::CollectGroundItemRequestArgsToJsonString(const UCollectGroundItemRequestArgs* Serializable, const bool Pretty)
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

UCollectGroundItemRequestArgs* UCollectGroundItemRequestArgsLibrary::Make(FString GroundItemId, UObject* Outer)
{
	auto Serializable = NewObject<UCollectGroundItemRequestArgs>(Outer);
	Serializable->GroundItemId = GroundItemId;
	
	return Serializable;
}

void UCollectGroundItemRequestArgsLibrary::Break(const UCollectGroundItemRequestArgs* Serializable, FString& GroundItemId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GroundItemId = Serializable->GroundItemId;
	}
		
}

