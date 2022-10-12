
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "GetManifestsRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetManifestsRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset")
	FOptionalInt32 Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	FOptionalBool bArchived;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};