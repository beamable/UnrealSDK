
#include "AutoGen/DeleteExternalIdentityApiRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UDeleteExternalIdentityApiRequestBodyLibrary::DeleteExternalIdentityApiRequestBodyToJsonString(const UDeleteExternalIdentityApiRequestBody* Serializable, const bool Pretty)
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

UDeleteExternalIdentityApiRequestBody* UDeleteExternalIdentityApiRequestBodyLibrary::Make(FString ProviderAddress, FString UserId, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteExternalIdentityApiRequestBody>(Outer);
	Serializable->ProviderAddress = ProviderAddress;
	Serializable->UserId = UserId;
	
	return Serializable;
}

void UDeleteExternalIdentityApiRequestBodyLibrary::Break(const UDeleteExternalIdentityApiRequestBody* Serializable, FString& ProviderAddress, FString& UserId)
{
	ProviderAddress = Serializable->ProviderAddress;
	UserId = Serializable->UserId;
		
}

