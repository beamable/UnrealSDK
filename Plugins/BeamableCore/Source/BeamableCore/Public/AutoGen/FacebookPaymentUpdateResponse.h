
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "FacebookPaymentUpdateResponse.generated.h"

UCLASS(BlueprintType)
class UFacebookPaymentUpdateResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Result")
	FString Result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Type")
	FString ContentType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};