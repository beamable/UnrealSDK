
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary::StandaloneMicroserviceJoinNumbersAsStringRequestArgsToJsonString(const UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Serializable, const bool Pretty)
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

UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* UStandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary::Make(int32 A, int32 B, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceJoinNumbersAsStringRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UStandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary::Break(const UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Serializable, int32& A, int32& B)
{
	A = Serializable->A;
	B = Serializable->B;
		
}

