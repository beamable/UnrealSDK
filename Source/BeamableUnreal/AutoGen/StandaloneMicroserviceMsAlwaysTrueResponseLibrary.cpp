
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAlwaysTrueResponseLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceMsAlwaysTrueResponseLibrary::StandaloneMicroserviceMsAlwaysTrueResponseToJsonString(const UStandaloneMicroserviceMsAlwaysTrueResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UStandaloneMicroserviceMsAlwaysTrueResponse* UStandaloneMicroserviceMsAlwaysTrueResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceMsAlwaysTrueResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void UStandaloneMicroserviceMsAlwaysTrueResponseLibrary::Break(const UStandaloneMicroserviceMsAlwaysTrueResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

