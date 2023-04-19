
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAddResponseLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceMsAddResponseLibrary::StandaloneMicroserviceMsAddResponseToJsonString(const UStandaloneMicroserviceMsAddResponse* Serializable, const bool Pretty)
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

UStandaloneMicroserviceMsAddResponse* UStandaloneMicroserviceMsAddResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceMsAddResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UStandaloneMicroserviceMsAddResponseLibrary::Break(const UStandaloneMicroserviceMsAddResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

