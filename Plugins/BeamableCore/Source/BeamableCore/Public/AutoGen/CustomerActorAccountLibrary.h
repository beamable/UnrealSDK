#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorAccount.h"

#include "CustomerActorAccountLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorAccount To JSON String")
	static FString CustomerActorAccountToJsonString(const UCustomerActorAccount* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorAccount", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccountId, CreatedTimeMs, UpdatedTimeMs, Email, Password, Username, Country, Language, RoleString, RealmId, RealmAssociations, ThirdPartyAssociations, External, Roles, DeviceIds, Outer", NativeMakeFunc))
	static UCustomerActorAccount* Make(FOptionalInt64 AccountId, FOptionalInt64 CreatedTimeMs, FOptionalInt64 UpdatedTimeMs, FOptionalString Email, FOptionalString Password, FOptionalString Username, FOptionalString Country, FOptionalString Language, FOptionalString RoleString, FOptionalString RealmId, FOptionalArrayOfRealmAssociation RealmAssociations, FOptionalArrayOfThirdPartyAssociation ThirdPartyAssociations, FOptionalArrayOfBeamExternalIdentity External, FOptionalArrayOfRoleAssociation Roles, FOptionalArrayOfString DeviceIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorAccount", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorAccount* Serializable, FOptionalInt64& AccountId, FOptionalInt64& CreatedTimeMs, FOptionalInt64& UpdatedTimeMs, FOptionalString& Email, FOptionalString& Password, FOptionalString& Username, FOptionalString& Country, FOptionalString& Language, FOptionalString& RoleString, FOptionalString& RealmId, FOptionalArrayOfRealmAssociation& RealmAssociations, FOptionalArrayOfThirdPartyAssociation& ThirdPartyAssociations, FOptionalArrayOfBeamExternalIdentity& External, FOptionalArrayOfRoleAssociation& Roles, FOptionalArrayOfString& DeviceIds);
};