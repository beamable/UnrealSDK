
#include "BeamableCore/Public/AutoGen/GetCatalogResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetCatalogResponseLibrary::GetCatalogResponseToJsonString(const UGetCatalogResponse* Serializable, const bool Pretty)
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

UGetCatalogResponse* UGetCatalogResponseLibrary::Make(FOptionalCatalog Catalog, UObject* Outer)
{
	auto Serializable = NewObject<UGetCatalogResponse>(Outer);
	Serializable->Catalog = Catalog;
	
	return Serializable;
}

void UGetCatalogResponseLibrary::Break(const UGetCatalogResponse* Serializable, FOptionalCatalog& Catalog)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Catalog = Serializable->Catalog;
	}
		
}

