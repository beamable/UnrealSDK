
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalVariableReference.h"

#include "RouteParameter.generated.h"

UCLASS(BlueprintType)
class URouteParameter : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type Name")
	FString TypeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Variable Ref")
	FOptionalVariableReference VariableRef;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};