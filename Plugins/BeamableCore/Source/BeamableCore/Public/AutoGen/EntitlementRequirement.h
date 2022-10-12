
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "EntitlementRequirement.generated.h"

UCLASS(BlueprintType)
class UEntitlementRequirement : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Constraint")
	FString Constraint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Specialization")
	FOptionalString Specialization;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};