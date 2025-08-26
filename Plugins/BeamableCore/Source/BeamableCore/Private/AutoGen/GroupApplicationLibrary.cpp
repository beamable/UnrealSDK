
#include "BeamableCore/Public/AutoGen/GroupApplicationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupApplicationLibrary::GroupApplicationToJsonString(const UGroupApplication* Serializable, const bool Pretty)
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

UGroupApplication* UGroupApplicationLibrary::Make(FOptionalInt64 SubGroup, UObject* Outer)
{
	auto Serializable = NewObject<UGroupApplication>(Outer);
	Serializable->SubGroup = SubGroup;
	
	return Serializable;
}

void UGroupApplicationLibrary::Break(const UGroupApplication* Serializable, FOptionalInt64& SubGroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SubGroup = Serializable->SubGroup;
	}
		
}

