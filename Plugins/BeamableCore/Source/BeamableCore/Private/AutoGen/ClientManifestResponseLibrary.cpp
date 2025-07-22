
#include "BeamableCore/Public/AutoGen/ClientManifestResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UClientManifestResponseLibrary::ClientManifestResponseToJsonString(const UClientManifestResponse* Serializable, const bool Pretty)
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

UClientManifestResponse* UClientManifestResponseLibrary::Make(TArray<UClientContentInfo*> Items, UObject* Outer)
{
	auto Serializable = NewObject<UClientManifestResponse>(Outer);
	Serializable->Items = Items;
	
	return Serializable;
}

void UClientManifestResponseLibrary::Break(const UClientManifestResponse* Serializable, TArray<UClientContentInfo*>& Items)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Items = Serializable->Items;
	}
		
}

