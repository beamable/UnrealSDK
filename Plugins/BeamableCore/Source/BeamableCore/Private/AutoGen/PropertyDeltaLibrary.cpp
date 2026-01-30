
#include "BeamableCore/Public/AutoGen/PropertyDeltaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPropertyDeltaLibrary::PropertyDeltaToJsonString(const UPropertyDelta* Serializable, const bool Pretty)
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

UPropertyDelta* UPropertyDeltaLibrary::Make(FOptionalString Before, FOptionalString After, UObject* Outer)
{
	auto Serializable = NewObject<UPropertyDelta>(Outer);
	Serializable->Before = Before;
	Serializable->After = After;
	
	return Serializable;
}

void UPropertyDeltaLibrary::Break(const UPropertyDelta* Serializable, FOptionalString& Before, FOptionalString& After)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Before = Serializable->Before;
		After = Serializable->After;
	}
		
}

