
#include "BeamableCore/Public/AutoGen/DeleteRegistrationRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UDeleteRegistrationRequestBodyLibrary::DeleteRegistrationRequestBodyToJsonString(const UDeleteRegistrationRequestBody* Serializable, const bool Pretty)
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

UDeleteRegistrationRequestBody* UDeleteRegistrationRequestBodyLibrary::Make(FOptionalString RoutingKey, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteRegistrationRequestBody>(Outer);
	Serializable->RoutingKey = RoutingKey;
	
	return Serializable;
}

void UDeleteRegistrationRequestBodyLibrary::Break(const UDeleteRegistrationRequestBody* Serializable, FOptionalString& RoutingKey)
{
	RoutingKey = Serializable->RoutingKey;
		
}

