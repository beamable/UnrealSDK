
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "GetActiveListingRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetActiveListingRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listing")
	FString Listing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Store")
	FOptionalString Store;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time")
	FOptionalString Time;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};