
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAttachExternalIdentityApiResponseLibrary::AttachExternalIdentityApiResponseToJsonString(const UAttachExternalIdentityApiResponse* Serializable, const bool Pretty)
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

UAttachExternalIdentityApiResponse* UAttachExternalIdentityApiResponseLibrary::Make(FString Result, FOptionalString ChallengeToken, UObject* Outer)
{
	auto Serializable = NewObject<UAttachExternalIdentityApiResponse>(Outer);
	Serializable->Result = Result;
	Serializable->ChallengeToken = ChallengeToken;
	
	return Serializable;
}

void UAttachExternalIdentityApiResponseLibrary::Break(const UAttachExternalIdentityApiResponse* Serializable, FString& Result, FOptionalString& ChallengeToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		ChallengeToken = Serializable->ChallengeToken;
	}
		
}

