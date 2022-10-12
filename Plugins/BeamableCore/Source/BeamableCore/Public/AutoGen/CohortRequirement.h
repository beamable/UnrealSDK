
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "CohortRequirement.generated.h"

UCLASS(BlueprintType)
class UCohortRequirement : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Trial")
	FString Trial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort")
	FString Cohort;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Constraint")
	FString Constraint;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};