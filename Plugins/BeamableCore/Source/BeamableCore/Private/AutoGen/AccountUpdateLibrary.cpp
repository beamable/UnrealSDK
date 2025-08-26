
#include "BeamableCore/Public/AutoGen/AccountUpdateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountUpdateLibrary::AccountUpdateToJsonString(const UAccountUpdate* Serializable, const bool Pretty)
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

UAccountUpdate* UAccountUpdateLibrary::Make(bool bHasThirdPartyToken, FOptionalString ThirdParty, FOptionalString Country, FOptionalString Language, FOptionalGamerTagAssociation GamerTagAssoc, FOptionalString Token, FOptionalString DeviceId, FOptionalString UserName, FOptionalArrayOfBeamExternalIdentity External, UObject* Outer)
{
	auto Serializable = NewObject<UAccountUpdate>(Outer);
	Serializable->bHasThirdPartyToken = bHasThirdPartyToken;
	Serializable->ThirdParty = ThirdParty;
	Serializable->Country = Country;
	Serializable->Language = Language;
	Serializable->GamerTagAssoc = GamerTagAssoc;
	Serializable->Token = Token;
	Serializable->DeviceId = DeviceId;
	Serializable->UserName = UserName;
	Serializable->External = External;
	
	return Serializable;
}

void UAccountUpdateLibrary::Break(const UAccountUpdate* Serializable, bool& bHasThirdPartyToken, FOptionalString& ThirdParty, FOptionalString& Country, FOptionalString& Language, FOptionalGamerTagAssociation& GamerTagAssoc, FOptionalString& Token, FOptionalString& DeviceId, FOptionalString& UserName, FOptionalArrayOfBeamExternalIdentity& External)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bHasThirdPartyToken = Serializable->bHasThirdPartyToken;
		ThirdParty = Serializable->ThirdParty;
		Country = Serializable->Country;
		Language = Serializable->Language;
		GamerTagAssoc = Serializable->GamerTagAssoc;
		Token = Serializable->Token;
		DeviceId = Serializable->DeviceId;
		UserName = Serializable->UserName;
		External = Serializable->External;
	}
		
}

