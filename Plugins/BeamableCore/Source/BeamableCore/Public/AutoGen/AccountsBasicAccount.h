
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/GamerTagAssociation.h"
#include "AutoGen/Optionals/OptionalArrayOfRoleMapping.h"
#include "AutoGen/ThirdPartyAssociation.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "AccountsBasicAccount.generated.h"

UCLASS(BlueprintType)
class UAccountsBasicAccount : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight")
	FOptionalArrayOfInFlightMessage InFlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Time Millis")
	int64 CreatedTimeMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id")
	FOptionalString RealmId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FOptionalString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role String")
	FOptionalString RoleString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids")
	FOptionalArrayOfString DeviceIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Privileged Account")
	bool bPrivilegedAccount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country")
	FOptionalString Country;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Was Migrated")
	FOptionalBool bWasMigrated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tags")
	TArray<UGamerTagAssociation*> GamerTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles")
	FOptionalArrayOfRoleMapping Roles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated Time Millis")
	int64 UpdatedTimeMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Parties")
	TArray<UThirdPartyAssociation*> ThirdParties;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id")
	FOptionalString DeviceId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Name")
	FOptionalString UserName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Heartbeat")
	FOptionalInt64 Heartbeat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password")
	FOptionalString Password;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};