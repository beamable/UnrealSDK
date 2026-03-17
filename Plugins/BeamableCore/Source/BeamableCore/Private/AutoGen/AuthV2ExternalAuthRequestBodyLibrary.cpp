
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ExternalAuthRequestBodyLibrary::AuthV2ExternalAuthRequestBodyToJsonString(const UAuthV2ExternalAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2ExternalAuthRequestBody* UAuthV2ExternalAuthRequestBodyLibrary::Make(FOptionalBool bHasProviderNamespace, FOptionalString Provider, FOptionalString ProviderNamespace, FOptionalString Token, FOptionalAuthV2ChallengeSolution ChallengeSolution, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ExternalAuthRequestBody>(Outer);
	Serializable->bHasProviderNamespace = bHasProviderNamespace;
	Serializable->Provider = Provider;
	Serializable->ProviderNamespace = ProviderNamespace;
	Serializable->Token = Token;
	Serializable->ChallengeSolution = ChallengeSolution;
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void UAuthV2ExternalAuthRequestBodyLibrary::Break(const UAuthV2ExternalAuthRequestBody* Serializable, FOptionalBool& bHasProviderNamespace, FOptionalString& Provider, FOptionalString& ProviderNamespace, FOptionalString& Token, FOptionalAuthV2ChallengeSolution& ChallengeSolution, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bHasProviderNamespace = Serializable->bHasProviderNamespace;
		Provider = Serializable->Provider;
		ProviderNamespace = Serializable->ProviderNamespace;
		Token = Serializable->Token;
		ChallengeSolution = Serializable->ChallengeSolution;
		Scope = Serializable->Scope;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

