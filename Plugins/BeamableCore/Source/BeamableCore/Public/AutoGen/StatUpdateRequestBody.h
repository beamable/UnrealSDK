
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "StatUpdateRequestBody.generated.h"

UCLASS(BlueprintType)
class UStatUpdateRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FOptionalString ObjectId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Set")
	FOptionalMapOfString Set;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add")
	FOptionalMapOfString Add;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Emit Analytics")
	FOptionalBool bEmitAnalytics;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};