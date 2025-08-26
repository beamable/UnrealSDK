
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeleteThirdPartyAssociationLibrary::DeleteThirdPartyAssociationToJsonString(const UDeleteThirdPartyAssociation* Serializable, const bool Pretty)
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

UDeleteThirdPartyAssociation* UDeleteThirdPartyAssociationLibrary::Make(FString ThirdParty, FString UserAppId, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteThirdPartyAssociation>(Outer);
	Serializable->ThirdParty = ThirdParty;
	Serializable->UserAppId = UserAppId;
	
	return Serializable;
}

void UDeleteThirdPartyAssociationLibrary::Break(const UDeleteThirdPartyAssociation* Serializable, FString& ThirdParty, FString& UserAppId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ThirdParty = Serializable->ThirdParty;
		UserAppId = Serializable->UserAppId;
	}
		
}

