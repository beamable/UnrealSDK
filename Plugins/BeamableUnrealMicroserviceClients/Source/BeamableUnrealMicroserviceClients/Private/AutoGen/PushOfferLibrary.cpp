
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushOfferLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPushOfferLibrary::PushOfferToJsonString(const UPushOffer* Serializable, const bool Pretty)
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

UPushOffer* UPushOfferLibrary::Make(FString ItemId, FString Value, FString CustomData, UObject* Outer)
{
	auto Serializable = NewObject<UPushOffer>(Outer);
	Serializable->ItemId = ItemId;
	Serializable->Value = Value;
	Serializable->CustomData = CustomData;
	
	return Serializable;
}

void UPushOfferLibrary::Break(const UPushOffer* Serializable, FString& ItemId, FString& Value, FString& CustomData)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ItemId = Serializable->ItemId;
		Value = Serializable->Value;
		CustomData = Serializable->CustomData;
	}
		
}

