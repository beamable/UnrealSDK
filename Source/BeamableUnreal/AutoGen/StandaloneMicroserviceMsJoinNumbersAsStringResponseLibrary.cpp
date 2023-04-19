
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary::StandaloneMicroserviceMsJoinNumbersAsStringResponseToJsonString(const UStandaloneMicroserviceMsJoinNumbersAsStringResponse* Serializable, const bool Pretty)
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

UStandaloneMicroserviceMsJoinNumbersAsStringResponse* UStandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary::Make(FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceMsJoinNumbersAsStringResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UStandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary::Break(const UStandaloneMicroserviceMsJoinNumbersAsStringResponse* Serializable, FString& Value)
{
	Value = Serializable->Value;
		
}

