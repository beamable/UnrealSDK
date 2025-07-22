
#include "BeamableCore/Public/AutoGen/AccountsObjectAccountLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountsObjectAccountLibrary::AccountsObjectAccountToJsonString(const UAccountsObjectAccount* Serializable, const bool Pretty)
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

UAccountsObjectAccount* UAccountsObjectAccountLibrary::Make(bool bPrivilegedAccount, FBeamAccountId Id, int64 CreatedTimeMillis, int64 UpdatedTimeMillis, TArray<UThirdPartyAssociation*> ThirdParties, TArray<FBeamExternalIdentity> External, TArray<UGamerTagAssociation*> GamerTags, FOptionalBool bWasMigrated, FOptionalString UserName, FOptionalString DeviceId, FOptionalString Language, FOptionalString Password, FOptionalString Country, FOptionalString RoleString, FOptionalString Email, FOptionalString RealmId, FOptionalInt64 Heartbeat, FOptionalArrayOfRoleMapping Roles, FOptionalArrayOfString DeviceIds, FOptionalArrayOfInFlightMessage InFlight, UObject* Outer)
{
	auto Serializable = NewObject<UAccountsObjectAccount>(Outer);
	Serializable->bPrivilegedAccount = bPrivilegedAccount;
	Serializable->Id = Id;
	Serializable->CreatedTimeMillis = CreatedTimeMillis;
	Serializable->UpdatedTimeMillis = UpdatedTimeMillis;
	Serializable->ThirdParties = ThirdParties;
	Serializable->External = External;
	Serializable->GamerTags = GamerTags;
	Serializable->bWasMigrated = bWasMigrated;
	Serializable->UserName = UserName;
	Serializable->DeviceId = DeviceId;
	Serializable->Language = Language;
	Serializable->Password = Password;
	Serializable->Country = Country;
	Serializable->RoleString = RoleString;
	Serializable->Email = Email;
	Serializable->RealmId = RealmId;
	Serializable->Heartbeat = Heartbeat;
	Serializable->Roles = Roles;
	Serializable->DeviceIds = DeviceIds;
	Serializable->InFlight = InFlight;
	
	return Serializable;
}

void UAccountsObjectAccountLibrary::Break(const UAccountsObjectAccount* Serializable, bool& bPrivilegedAccount, FBeamAccountId& Id, int64& CreatedTimeMillis, int64& UpdatedTimeMillis, TArray<UThirdPartyAssociation*>& ThirdParties, TArray<FBeamExternalIdentity>& External, TArray<UGamerTagAssociation*>& GamerTags, FOptionalBool& bWasMigrated, FOptionalString& UserName, FOptionalString& DeviceId, FOptionalString& Language, FOptionalString& Password, FOptionalString& Country, FOptionalString& RoleString, FOptionalString& Email, FOptionalString& RealmId, FOptionalInt64& Heartbeat, FOptionalArrayOfRoleMapping& Roles, FOptionalArrayOfString& DeviceIds, FOptionalArrayOfInFlightMessage& InFlight)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bPrivilegedAccount = Serializable->bPrivilegedAccount;
		Id = Serializable->Id;
		CreatedTimeMillis = Serializable->CreatedTimeMillis;
		UpdatedTimeMillis = Serializable->UpdatedTimeMillis;
		ThirdParties = Serializable->ThirdParties;
		External = Serializable->External;
		GamerTags = Serializable->GamerTags;
		bWasMigrated = Serializable->bWasMigrated;
		UserName = Serializable->UserName;
		DeviceId = Serializable->DeviceId;
		Language = Serializable->Language;
		Password = Serializable->Password;
		Country = Serializable->Country;
		RoleString = Serializable->RoleString;
		Email = Serializable->Email;
		RealmId = Serializable->RealmId;
		Heartbeat = Serializable->Heartbeat;
		Roles = Serializable->Roles;
		DeviceIds = Serializable->DeviceIds;
		InFlight = Serializable->InFlight;
	}
		
}

