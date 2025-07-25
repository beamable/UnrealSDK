
#include "BeamableCore/Public/AutoGen/StatStringListEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatStringListEntryLibrary::StatStringListEntryToJsonString(const UStatStringListEntry* Serializable, const bool Pretty)
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

UStatStringListEntry* UStatStringListEntryLibrary::Make(FString K, FString V, UObject* Outer)
{
	auto Serializable = NewObject<UStatStringListEntry>(Outer);
	Serializable->K = K;
	Serializable->V = V;
	
	return Serializable;
}

void UStatStringListEntryLibrary::Break(const UStatStringListEntry* Serializable, FString& K, FString& V)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		K = Serializable->K;
		V = Serializable->V;
	}
		
}

