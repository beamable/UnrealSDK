
#include "BeamableCore/Public/AutoGen/PropertyFilterDTOLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPropertyFilterDTOLibrary::PropertyFilterDTOToJsonString(const UPropertyFilterDTO* Serializable, const bool Pretty)
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

UPropertyFilterDTO* UPropertyFilterDTOLibrary::Make(FString Key, UPredicateDTO* Predicate, UObject* Outer)
{
	auto Serializable = NewObject<UPropertyFilterDTO>(Outer);
	Serializable->Key = Key;
	Serializable->Predicate = Predicate;
	
	return Serializable;
}

void UPropertyFilterDTOLibrary::Break(const UPropertyFilterDTO* Serializable, FString& Key, UPredicateDTO*& Predicate)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Key = Serializable->Key;
		Predicate = Serializable->Predicate;
	}
		
}

