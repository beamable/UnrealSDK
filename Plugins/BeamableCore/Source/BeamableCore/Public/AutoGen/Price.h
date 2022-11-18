
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalArrayOfInt32.h"

#include "Price.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPrice : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount", Category="Beam")
	FOptionalInt32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule", Category="Beam")
	FOptionalArrayOfInt32 Schedule;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};