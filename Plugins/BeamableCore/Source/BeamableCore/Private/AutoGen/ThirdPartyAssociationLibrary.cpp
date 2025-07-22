
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

UThirdPartyAssociation* UThirdPartyAssociationLibrary::Make(FString Name, FString UserAppId, FString AppId, TMap<FString, FString> Meta, FOptionalString Email, FOptionalString UserBusinessId, UObject* Outer)
{
	auto Serializable = NewObject<UThirdPartyAssociation>(Outer);
	Serializable->Name = Name;
	Serializable->UserAppId = UserAppId;
	Serializable->AppId = AppId;
	Serializable->Meta = Meta;
	Serializable->Email = Email;
	Serializable->UserBusinessId = UserBusinessId;
	
	return Serializable;
}

void UThirdPartyAssociationLibrary::Break(const UThirdPartyAssociation* Serializable, FString& Name, FString& UserAppId, FString& AppId, TMap<FString, FString>& Meta, FOptionalString& Email, FOptionalString& UserBusinessId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		UserAppId = Serializable->UserAppId;
		AppId = Serializable->AppId;
		Meta = Serializable->Meta;
		Email = Serializable->Email;
		UserBusinessId = Serializable->UserBusinessId;
	}
		
}

