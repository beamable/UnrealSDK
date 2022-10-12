
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ThirdPartyAssociation.h"

#include "TransferThirdPartyAssociation.generated.h"

UCLASS(BlueprintType)
class UTransferThirdPartyAssociation : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From Account Id")
	int64 FromAccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party")
	UThirdPartyAssociation* ThirdParty;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};