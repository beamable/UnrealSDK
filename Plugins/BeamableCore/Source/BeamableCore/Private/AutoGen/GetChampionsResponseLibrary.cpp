
#include "BeamableCore/Public/AutoGen/GetChampionsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetChampionsResponseLibrary::GetChampionsResponseToJsonString(const UGetChampionsResponse* Serializable, const bool Pretty)
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

UGetChampionsResponse* UGetChampionsResponseLibrary::Make(TArray<UChampionScore*> Entries, UObject* Outer)
{
	auto Serializable = NewObject<UGetChampionsResponse>(Outer);
	Serializable->Entries = Entries;
	
	return Serializable;
}

void UGetChampionsResponseLibrary::Break(const UGetChampionsResponse* Serializable, TArray<UChampionScore*>& Entries)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Entries = Serializable->Entries;
	}
		
}

