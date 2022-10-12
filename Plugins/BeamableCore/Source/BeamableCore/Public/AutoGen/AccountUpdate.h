
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalGamerTagAssociation.h"

#include "AccountUpdate.generated.h"

UCLASS(BlueprintType)
class UAccountUpdate : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party")
	FOptionalString ThirdParty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Third Party Token")
	bool bHasThirdPartyToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country")
	FOptionalString Country;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Assoc")
	FOptionalGamerTagAssociation GamerTagAssoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	FOptionalString Token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id")
	FOptionalString DeviceId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Name")
	FOptionalString UserName;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};