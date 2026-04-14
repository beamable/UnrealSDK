
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UThirdPartyAssociationLibrary::ThirdPartyAssociationToJsonString(const UThirdPartyAssociation* Serializable, const bool Pretty)
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

UThirdPartyAssociation* UThirdPartyAssociationLibrary::Make(FOptionalString Name, FOptionalString AppId, FOptionalString UserAppId, FOptionalString UserBusinessId, FOptionalString Email, FOptionalMapOfString Meta, UObject* Outer)
{
	auto Serializable = NewObject<UThirdPartyAssociation>(Outer);
	Serializable->Name = Name;
	Serializable->AppId = AppId;
	Serializable->UserAppId = UserAppId;
	Serializable->UserBusinessId = UserBusinessId;
	Serializable->Email = Email;
	Serializable->Meta = Meta;
	
	return Serializable;
}

void UThirdPartyAssociationLibrary::Break(const UThirdPartyAssociation* Serializable, FOptionalString& Name, FOptionalString& AppId, FOptionalString& UserAppId, FOptionalString& UserBusinessId, FOptionalString& Email, FOptionalMapOfString& Meta)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		AppId = Serializable->AppId;
		UserAppId = Serializable->UserAppId;
		UserBusinessId = Serializable->UserBusinessId;
		Email = Serializable->Email;
		Meta = Serializable->Meta;
	}
		
}

