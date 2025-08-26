
#include "BeamableCore/Public/AutoGen/GetManifestHistoryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestHistoryRequestBodyLibrary::GetManifestHistoryRequestBodyToJsonString(const UGetManifestHistoryRequestBody* Serializable, const bool Pretty)
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

UGetManifestHistoryRequestBody* UGetManifestHistoryRequestBodyLibrary::Make(FOptionalBeamContentManifestId Id, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestHistoryRequestBody>(Outer);
	Serializable->Id = Id;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UGetManifestHistoryRequestBodyLibrary::Break(const UGetManifestHistoryRequestBody* Serializable, FOptionalBeamContentManifestId& Id, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Limit = Serializable->Limit;
	}
		
}

