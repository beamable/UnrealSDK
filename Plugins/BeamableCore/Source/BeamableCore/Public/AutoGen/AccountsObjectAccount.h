#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/GamerTagAssociation.h"
#include "BeamBackend/ReplacementTypes/BeamExternalIdentity.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRoleMapping.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociation.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "AccountsObjectAccount.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAccountsObjectAccount : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Privileged Account", Category="Beam")
	bool bPrivilegedAccount = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FBeamAccountId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Time Millis", Category="Beam")
	int64 CreatedTimeMillis = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated Time Millis", Category="Beam")
	int64 UpdatedTimeMillis = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Parties", Category="Beam")
	TArray<UThirdPartyAssociation*> ThirdParties = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	TArray<FBeamExternalIdentity> External = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tags", Category="Beam")
	TArray<UGamerTagAssociation*> GamerTags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Was Migrated", Category="Beam")
	FOptionalBool bWasMigrated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Name", Category="Beam")
	FOptionalString UserName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id", Category="Beam")
	FOptionalString DeviceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FOptionalString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country", Category="Beam")
	FOptionalString Country = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role String", Category="Beam")
	FOptionalString RoleString = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FOptionalString RealmId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Heartbeat", Category="Beam")
	FOptionalInt64 Heartbeat = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles", Category="Beam")
	FOptionalArrayOfRoleMapping Roles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids", Category="Beam")
	FOptionalArrayOfString DeviceIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight", Category="Beam")
	FOptionalArrayOfInFlightMessage InFlight = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};