
#include "BeamableCore/Public/AutoGen/DeleteExternalIdentityApiRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeleteExternalIdentityApiRequestBodyLibrary::DeleteExternalIdentityApiRequestBodyToJsonString(const UDeleteExternalIdentityApiRequestBody* Serializable, const bool Pretty)
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

UDeleteExternalIdentityApiRequestBody* UDeleteExternalIdentityApiRequestBodyLibrary::Make(FString ProviderService, FString UserId, FOptionalString ProviderNamespace, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteExternalIdentityApiRequestBody>(Outer);
	Serializable->ProviderService = ProviderService;
	Serializable->UserId = UserId;
	Serializable->ProviderNamespace = ProviderNamespace;
	
	return Serializable;
}

void UDeleteExternalIdentityApiRequestBodyLibrary::Break(const UDeleteExternalIdentityApiRequestBody* Serializable, FString& ProviderService, FString& UserId, FOptionalString& ProviderNamespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProviderService = Serializable->ProviderService;
		UserId = Serializable->UserId;
		ProviderNamespace = Serializable->ProviderNamespace;
	}
		
}

