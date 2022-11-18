
#include "AutoGen/ExternalIdentityRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UExternalIdentityRequestBodyLibrary::ExternalIdentityRequestBodyToJsonString(const UExternalIdentityRequestBody* Serializable, const bool Pretty)
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

UExternalIdentityRequestBody* UExternalIdentityRequestBodyLibrary::Make(FString ProviderAddress, FString ExternalToken, FOptionalChallengeSolution ChallengeSolution, UObject* Outer)
{
	auto Serializable = NewObject<UExternalIdentityRequestBody>(Outer);
	Serializable->ProviderAddress = ProviderAddress;
	Serializable->ExternalToken = ExternalToken;
	Serializable->ChallengeSolution = ChallengeSolution;
	
	return Serializable;
}

void UExternalIdentityRequestBodyLibrary::Break(const UExternalIdentityRequestBody* Serializable, FString& ProviderAddress, FString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution)
{
	ProviderAddress = Serializable->ProviderAddress;
	ExternalToken = Serializable->ExternalToken;
	ChallengeSolution = Serializable->ChallengeSolution;
		
}

