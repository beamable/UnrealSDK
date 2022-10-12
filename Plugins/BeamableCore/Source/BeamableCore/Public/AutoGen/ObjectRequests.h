
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfObjectRequestBody.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "ObjectRequests.generated.h"

UCLASS(BlueprintType)
class UObjectRequests : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Request")
	FOptionalArrayOfObjectRequestBody Request;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FOptionalInt64 PlayerId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};