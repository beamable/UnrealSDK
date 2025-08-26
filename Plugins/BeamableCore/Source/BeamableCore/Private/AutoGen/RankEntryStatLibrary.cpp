
#include "BeamableCore/Public/AutoGen/RankEntryStatLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URankEntryStatLibrary::RankEntryStatToJsonString(const URankEntryStat* Serializable, const bool Pretty)
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

URankEntryStat* URankEntryStatLibrary::Make(FString Name, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<URankEntryStat>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void URankEntryStatLibrary::Break(const URankEntryStat* Serializable, FString& Name, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Value = Serializable->Value;
	}
		
}

