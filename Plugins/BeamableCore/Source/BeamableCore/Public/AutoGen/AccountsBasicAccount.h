
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
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

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountsBasicAccount : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Privileged Account", Category="Beam")
	bool bPrivilegedAccount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Time Millis", Category="Beam")
	int64 CreatedTimeMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated Time Millis", Category="Beam")
	int64 UpdatedTimeMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Parties", Category="Beam")
	TArray<UThirdPartyAssociation*> ThirdParties;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tags", Category="Beam")
	TArray<UGamerTagAssociation*> GamerTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Was Migrated", Category="Beam")
	FOptionalBool bWasMigrated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Name", Category="Beam")
	FOptionalString UserName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id", Category="Beam")
	FOptionalString DeviceId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FOptionalString Password;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country", Category="Beam")
	FOptionalString Country;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role String", Category="Beam")
	FOptionalString RoleString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FOptionalString RealmId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Heartbeat", Category="Beam")
	FOptionalInt64 Heartbeat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles", Category="Beam")
	FOptionalArrayOfRoleMapping Roles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids", Category="Beam")
	FOptionalArrayOfString DeviceIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight", Category="Beam")
	FOptionalArrayOfInFlightMessage InFlight;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};