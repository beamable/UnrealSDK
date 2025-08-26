
#include "BeamableCore/Public/AutoGen/ExternalIdentityAvailableApiRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UExternalIdentityAvailableApiRequestBodyLibrary::ExternalIdentityAvailableApiRequestBodyToJsonString(const UExternalIdentityAvailableApiRequestBody* Serializable, const bool Pretty)
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

UExternalIdentityAvailableApiRequestBody* UExternalIdentityAvailableApiRequestBodyLibrary::Make(FString ProviderService, FString UserId, FOptionalString ProviderNamespace, UObject* Outer)
{
	auto Serializable = NewObject<UExternalIdentityAvailableApiRequestBody>(Outer);
	Serializable->ProviderService = ProviderService;
	Serializable->UserId = UserId;
	Serializable->ProviderNamespace = ProviderNamespace;
	
	return Serializable;
}

void UExternalIdentityAvailableApiRequestBodyLibrary::Break(const UExternalIdentityAvailableApiRequestBody* Serializable, FString& ProviderService, FString& UserId, FOptionalString& ProviderNamespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProviderService = Serializable->ProviderService;
		UserId = Serializable->UserId;
		ProviderNamespace = Serializable->ProviderNamespace;
	}
		
}

