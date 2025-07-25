
#include "BeamableCore/Public/AutoGen/EraLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEraLibrary::EraToJsonString(const UEra* Serializable, const bool Pretty)
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

UEra* UEraLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UEra>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UEraLibrary::Break(const UEra* Serializable, int32& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Value = Serializable->Value;
	}
		
}

