
#include "BeamableCore/Public/AutoGen/CustomerActorAccountLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorAccountLibrary::CustomerActorAccountToJsonString(const UCustomerActorAccount* Serializable, const bool Pretty)
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

UCustomerActorAccount* UCustomerActorAccountLibrary::Make(FOptionalInt64 AccountId, FOptionalInt64 CreatedTimeMs, FOptionalInt64 UpdatedTimeMs, FOptionalString Email, FOptionalString Password, FOptionalString Username, FOptionalString Country, FOptionalString Language, FOptionalString RoleString, FOptionalString RealmId, FOptionalArrayOfRealmAssociation RealmAssociations, FOptionalArrayOfThirdPartyAssociation ThirdPartyAssociations, FOptionalArrayOfBeamExternalIdentity External, FOptionalArrayOfRoleAssociation Roles, FOptionalArrayOfString DeviceIds, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorAccount>(Outer);
	Serializable->AccountId = AccountId;
	Serializable->CreatedTimeMs = CreatedTimeMs;
	Serializable->UpdatedTimeMs = UpdatedTimeMs;
	Serializable->Email = Email;
	Serializable->Password = Password;
	Serializable->Username = Username;
	Serializable->Country = Country;
	Serializable->Language = Language;
	Serializable->RoleString = RoleString;
	Serializable->RealmId = RealmId;
	Serializable->RealmAssociations = RealmAssociations;
	Serializable->ThirdPartyAssociations = ThirdPartyAssociations;
	Serializable->External = External;
	Serializable->Roles = Roles;
	Serializable->DeviceIds = DeviceIds;
	
	return Serializable;
}

void UCustomerActorAccountLibrary::Break(const UCustomerActorAccount* Serializable, FOptionalInt64& AccountId, FOptionalInt64& CreatedTimeMs, FOptionalInt64& UpdatedTimeMs, FOptionalString& Email, FOptionalString& Password, FOptionalString& Username, FOptionalString& Country, FOptionalString& Language, FOptionalString& RoleString, FOptionalString& RealmId, FOptionalArrayOfRealmAssociation& RealmAssociations, FOptionalArrayOfThirdPartyAssociation& ThirdPartyAssociations, FOptionalArrayOfBeamExternalIdentity& External, FOptionalArrayOfRoleAssociation& Roles, FOptionalArrayOfString& DeviceIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccountId = Serializable->AccountId;
		CreatedTimeMs = Serializable->CreatedTimeMs;
		UpdatedTimeMs = Serializable->UpdatedTimeMs;
		Email = Serializable->Email;
		Password = Serializable->Password;
		Username = Serializable->Username;
		Country = Serializable->Country;
		Language = Serializable->Language;
		RoleString = Serializable->RoleString;
		RealmId = Serializable->RealmId;
		RealmAssociations = Serializable->RealmAssociations;
		ThirdPartyAssociations = Serializable->ThirdPartyAssociations;
		External = Serializable->External;
		Roles = Serializable->Roles;
		DeviceIds = Serializable->DeviceIds;
	}
		
}

