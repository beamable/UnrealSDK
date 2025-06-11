#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/RouteVariables.h"
#include "BeamableCore/Public/AutoGen/ServiceRoute.h"
#include "BeamableCore/Public/AutoGen/RouteParameters.h"

#include "WebhookComet.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UWebhookComet : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method", Category="Beam")
	FString Method = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Variables", Category="Beam")
	URouteVariables* Variables = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Route", Category="Beam")
	UServiceRoute* Route = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parameters", Category="Beam")
	URouteParameters* Parameters = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};