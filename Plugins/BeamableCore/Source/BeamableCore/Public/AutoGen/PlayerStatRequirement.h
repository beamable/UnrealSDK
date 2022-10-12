
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PlayerStatRequirement.generated.h"

UCLASS(BlueprintType)
class UPlayerStatRequirement : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Domain")
	FOptionalString Domain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat")
	FString Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Constraint")
	FString Constraint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value")
	FString Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access")
	FOptionalString Access;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};