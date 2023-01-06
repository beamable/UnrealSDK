
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

UExternalIdentity* UExternalIdentityLibrary::Make(FString ProviderService, FString UserId, FString ProviderNamespace, UObject* Outer)
{
	auto Serializable = NewObject<UExternalIdentity>(Outer);
	Serializable->ProviderService = ProviderService;
	Serializable->UserId = UserId;
	Serializable->ProviderNamespace = ProviderNamespace;
	
	return Serializable;
}

void UExternalIdentityLibrary::Break(const UExternalIdentity* Serializable, FString& ProviderService, FString& UserId, FString& ProviderNamespace)
{
	ProviderService = Serializable->ProviderService;
	UserId = Serializable->UserId;
	ProviderNamespace = Serializable->ProviderNamespace;
		
}

