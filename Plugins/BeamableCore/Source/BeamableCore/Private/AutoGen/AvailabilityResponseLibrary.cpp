
#include "BeamableCore/Public/AutoGen/AvailabilityResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAvailabilityResponseLibrary::AvailabilityResponseToJsonString(const UAvailabilityResponse* Serializable, const bool Pretty)
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

UAvailabilityResponse* UAvailabilityResponseLibrary::Make(bool bName, bool bTag, UObject* Outer)
{
	auto Serializable = NewObject<UAvailabilityResponse>(Outer);
	Serializable->bName = bName;
	Serializable->bTag = bTag;
	
	return Serializable;
}

void UAvailabilityResponseLibrary::Break(const UAvailabilityResponse* Serializable, bool& bName, bool& bTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bName = Serializable->bName;
		bTag = Serializable->bTag;
	}
		
}

