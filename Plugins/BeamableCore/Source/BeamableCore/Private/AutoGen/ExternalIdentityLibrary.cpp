
#include "AutoGen/ExternalIdentityLibrary.h"

#include "CoreMinimal.h"


FString UExternalIdentityLibrary::ExternalIdentityToJsonString(const UExternalIdentity* Serializable, const bool Pretty)
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

UExternalIdentity* UExternalIdentityLibrary::Make(FString ProviderAddress, FString UserId, UObject* Outer)
{
	auto Serializable = NewObject<UExternalIdentity>(Outer);
	Serializable->ProviderAddress = ProviderAddress;
	Serializable->UserId = UserId;
	
	return Serializable;
}

void UExternalIdentityLibrary::Break(const UExternalIdentity* Serializable, FString& ProviderAddress, FString& UserId)
{
	ProviderAddress = Serializable->ProviderAddress;
	UserId = Serializable->UserId;
		
}

