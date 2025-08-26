
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAttachExternalIdentityApiRequestBodyLibrary::AttachExternalIdentityApiRequestBodyToJsonString(const UAttachExternalIdentityApiRequestBody* Serializable, const bool Pretty)
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

UAttachExternalIdentityApiRequestBody* UAttachExternalIdentityApiRequestBodyLibrary::Make(FString ProviderService, FString ExternalToken, FOptionalChallengeSolution ChallengeSolution, FOptionalString ProviderNamespace, UObject* Outer)
{
	auto Serializable = NewObject<UAttachExternalIdentityApiRequestBody>(Outer);
	Serializable->ProviderService = ProviderService;
	Serializable->ExternalToken = ExternalToken;
	Serializable->ChallengeSolution = ChallengeSolution;
	Serializable->ProviderNamespace = ProviderNamespace;
	
	return Serializable;
}

void UAttachExternalIdentityApiRequestBodyLibrary::Break(const UAttachExternalIdentityApiRequestBody* Serializable, FString& ProviderService, FString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ProviderNamespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProviderService = Serializable->ProviderService;
		ExternalToken = Serializable->ExternalToken;
		ChallengeSolution = Serializable->ChallengeSolution;
		ProviderNamespace = Serializable->ProviderNamespace;
	}
		
}

