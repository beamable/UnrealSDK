
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAddRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceAddRequestArgsLibrary::StandaloneMicroserviceAddRequestArgsToJsonString(const UStandaloneMicroserviceAddRequestArgs* Serializable, const bool Pretty)
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

UStandaloneMicroserviceAddRequestArgs* UStandaloneMicroserviceAddRequestArgsLibrary::Make(int32 A, int32 B, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceAddRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UStandaloneMicroserviceAddRequestArgsLibrary::Break(const UStandaloneMicroserviceAddRequestArgs* Serializable, int32& A, int32& B)
{
	A = Serializable->A;
	B = Serializable->B;
		
}

