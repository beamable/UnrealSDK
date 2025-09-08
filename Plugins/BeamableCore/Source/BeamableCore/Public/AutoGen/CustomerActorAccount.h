#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealmAssociation.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfThirdPartyAssociation.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamExternalIdentity.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRoleAssociation.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

#include "CustomerActorAccount.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorAccount : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id", Category="Beam")
	FOptionalInt64 AccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Time Ms", Category="Beam")
	FOptionalInt64 CreatedTimeMs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated Time Ms", Category="Beam")
	FOptionalInt64 UpdatedTimeMs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FOptionalString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Username", Category="Beam")
	FOptionalString Username = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country", Category="Beam")
	FOptionalString Country = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role String", Category="Beam")
	FOptionalString RoleString = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FOptionalString RealmId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Associations", Category="Beam")
	FOptionalArrayOfRealmAssociation RealmAssociations = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party Associations", Category="Beam")
	FOptionalArrayOfThirdPartyAssociation ThirdPartyAssociations = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	FOptionalArrayOfBeamExternalIdentity External = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles", Category="Beam")
	FOptionalArrayOfRoleAssociation Roles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids", Category="Beam")
	FOptionalArrayOfString DeviceIds = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};