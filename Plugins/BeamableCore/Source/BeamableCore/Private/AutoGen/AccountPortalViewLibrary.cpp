
#include "BeamableCore/Public/AutoGen/AccountPortalViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountPortalViewLibrary::AccountPortalViewToJsonString(const UAccountPortalView* Serializable, const bool Pretty)
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

UAccountPortalView* UAccountPortalViewLibrary::Make(FBeamAccountId Id, TArray<FString> Scopes, TArray<FString> ThirdPartyAppAssociations, FOptionalString Email, FOptionalString RoleString, FOptionalString Language, FOptionalArrayOfBeamExternalIdentity External, FOptionalArrayOfRoleMapping Roles, UObject* Outer)
{
	auto Serializable = NewObject<UAccountPortalView>(Outer);
	Serializable->Id = Id;
	Serializable->Scopes = Scopes;
	Serializable->ThirdPartyAppAssociations = ThirdPartyAppAssociations;
	Serializable->Email = Email;
	Serializable->RoleString = RoleString;
	Serializable->Language = Language;
	Serializable->External = External;
	Serializable->Roles = Roles;
	
	return Serializable;
}

void UAccountPortalViewLibrary::Break(const UAccountPortalView* Serializable, FBeamAccountId& Id, TArray<FString>& Scopes, TArray<FString>& ThirdPartyAppAssociations, FOptionalString& Email, FOptionalString& RoleString, FOptionalString& Language, FOptionalArrayOfBeamExternalIdentity& External, FOptionalArrayOfRoleMapping& Roles)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Scopes = Serializable->Scopes;
		ThirdPartyAppAssociations = Serializable->ThirdPartyAppAssociations;
		Email = Serializable->Email;
		RoleString = Serializable->RoleString;
		Language = Serializable->Language;
		External = Serializable->External;
		Roles = Serializable->Roles;
	}
		
}

