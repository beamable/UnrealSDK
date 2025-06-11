#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamExternalIdentity.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGamerTagAssociation.h"

#include "AccountUpdate.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAccountUpdate : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Third Party Token", Category="Beam")
	bool bHasThirdPartyToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party", Category="Beam")
	FOptionalString ThirdParty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country", Category="Beam")
	FOptionalString Country = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Assoc", Category="Beam")
	FOptionalGamerTagAssociation GamerTagAssoc = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FOptionalString Token = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id", Category="Beam")
	FOptionalString DeviceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Name", Category="Beam")
	FOptionalString UserName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	FOptionalArrayOfBeamExternalIdentity External = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};