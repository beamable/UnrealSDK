
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/RouteVariables.h"
#include "AutoGen/ServiceRoute.h"
#include "AutoGen/RouteParameters.h"

#include "WebhookComet.generated.h"

UCLASS(BlueprintType)
class UWebhookComet : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method")
	FString Method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FOptionalString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Variables")
	URouteVariables* Variables;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Route")
	UServiceRoute* Route;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parameters")
	URouteParameters* Parameters;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};