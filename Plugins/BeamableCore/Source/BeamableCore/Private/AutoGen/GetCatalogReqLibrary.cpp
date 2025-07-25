
#include "BeamableCore/Public/AutoGen/GetCatalogReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetCatalogReqLibrary::GetCatalogReqToJsonString(const UGetCatalogReq* Serializable, const bool Pretty)
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

UGetCatalogReq* UGetCatalogReqLibrary::Make(FOptionalInt64 Version, UObject* Outer)
{
	auto Serializable = NewObject<UGetCatalogReq>(Outer);
	Serializable->Version = Version;
	
	return Serializable;
}

void UGetCatalogReqLibrary::Break(const UGetCatalogReq* Serializable, FOptionalInt64& Version)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Version = Serializable->Version;
	}
		
}

