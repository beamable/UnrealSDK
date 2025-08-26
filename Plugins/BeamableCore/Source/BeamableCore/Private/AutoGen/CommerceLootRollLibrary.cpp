
#include "BeamableCore/Public/AutoGen/CommerceLootRollLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCommerceLootRollLibrary::CommerceLootRollToJsonString(const UCommerceLootRoll* Serializable, const bool Pretty)
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

UCommerceLootRoll* UCommerceLootRollLibrary::Make(bool bPreroll, FOptionalArrayOfString ExternalTables, UObject* Outer)
{
	auto Serializable = NewObject<UCommerceLootRoll>(Outer);
	Serializable->bPreroll = bPreroll;
	Serializable->ExternalTables = ExternalTables;
	
	return Serializable;
}

void UCommerceLootRollLibrary::Break(const UCommerceLootRoll* Serializable, bool& bPreroll, FOptionalArrayOfString& ExternalTables)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bPreroll = Serializable->bPreroll;
		ExternalTables = Serializable->ExternalTables;
	}
		
}

