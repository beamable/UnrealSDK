
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "BeamoLimits.generated.h"

UCLASS(BlueprintType)
class UBeamoLimits : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Container Size")
	FString MaxContainerSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Running Containers Per Service")
	int32 MaxRunningContainersPerService;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};