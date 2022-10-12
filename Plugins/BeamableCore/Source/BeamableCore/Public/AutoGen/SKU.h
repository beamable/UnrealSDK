
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "SKU.generated.h"

UCLASS(BlueprintType)
class USKU : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Real Price")
	int32 RealPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Product Ids")
	TMap<FString, FString> ProductIds;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};