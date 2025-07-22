
#include "BeamableCore/Public/AutoGen/CatalogLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCatalogLibrary::CatalogToJsonString(const UCatalog* Serializable, const bool Pretty)
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

UCatalog* UCatalogLibrary::Make(int64 Version, int64 Created, TArray<UStore*> Stores, TArray<UOfferDefinition*> OfferDefinitions, UObject* Outer)
{
	auto Serializable = NewObject<UCatalog>(Outer);
	Serializable->Version = Version;
	Serializable->Created = Created;
	Serializable->Stores = Stores;
	Serializable->OfferDefinitions = OfferDefinitions;
	
	return Serializable;
}

void UCatalogLibrary::Break(const UCatalog* Serializable, int64& Version, int64& Created, TArray<UStore*>& Stores, TArray<UOfferDefinition*>& OfferDefinitions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Version = Serializable->Version;
		Created = Serializable->Created;
		Stores = Serializable->Stores;
		OfferDefinitions = Serializable->OfferDefinitions;
	}
		
}

