
#include "BeamableCore/Public/AutoGen/SaveCatalogRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveCatalogRequestBodyLibrary::SaveCatalogRequestBodyToJsonString(const USaveCatalogRequestBody* Serializable, const bool Pretty)
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

USaveCatalogRequestBody* USaveCatalogRequestBodyLibrary::Make(TArray<UStore*> Stores, TArray<UOfferDefinition*> OfferDefinitions, UObject* Outer)
{
	auto Serializable = NewObject<USaveCatalogRequestBody>(Outer);
	Serializable->Stores = Stores;
	Serializable->OfferDefinitions = OfferDefinitions;
	
	return Serializable;
}

void USaveCatalogRequestBodyLibrary::Break(const USaveCatalogRequestBody* Serializable, TArray<UStore*>& Stores, TArray<UOfferDefinition*>& OfferDefinitions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Stores = Serializable->Stores;
		OfferDefinitions = Serializable->OfferDefinitions;
	}
		
}

