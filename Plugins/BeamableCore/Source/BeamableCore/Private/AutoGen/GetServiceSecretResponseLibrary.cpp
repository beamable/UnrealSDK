
#include "BeamableCore/Public/AutoGen/GetServiceSecretResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetServiceSecretResponseLibrary::GetServiceSecretResponseToJsonString(const UGetServiceSecretResponse* Serializable, const bool Pretty)
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

UGetServiceSecretResponse* UGetServiceSecretResponseLibrary::Make(FOptionalString Secret, UObject* Outer)
{
	auto Serializable = NewObject<UGetServiceSecretResponse>(Outer);
	Serializable->Secret = Secret;
	
	return Serializable;
}

void UGetServiceSecretResponseLibrary::Break(const UGetServiceSecretResponse* Serializable, FOptionalString& Secret)
{
	Secret = Serializable->Secret;
		
}

