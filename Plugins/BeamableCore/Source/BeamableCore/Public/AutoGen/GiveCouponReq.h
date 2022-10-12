
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "GiveCouponReq.generated.h"

UCLASS(BlueprintType)
class UGiveCouponReq : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listing")
	FString Listing;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};