
#include "BeamableCore/Public/AutoGen/GetManifestHistoryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestHistoryResponseLibrary::GetManifestHistoryResponseToJsonString(const UGetManifestHistoryResponse* Serializable, const bool Pretty)
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

UGetManifestHistoryResponse* UGetManifestHistoryResponseLibrary::Make(TArray<UManifestSummary*> Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestHistoryResponse>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UGetManifestHistoryResponseLibrary::Break(const UGetManifestHistoryResponse* Serializable, TArray<UManifestSummary*>& Manifests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifests = Serializable->Manifests;
	}
		
}

